import chess
import chess.engine
import chess.pgn
import argparse
from typing import List
from pathlib import Path

def select_games(infile: str = "data/lichess_db_standard_rated_2013-01.pgn") -> List[int]:
    
    game_locations = []
    num_games = 2000
    pgn = open(infile)
    i = 0
    
    # Skimming
    while (i < num_games):
        game_location = pgn.tell()
        
        headers = chess.pgn.read_headers(pgn)
        if headers is None:
            break
        
        # Conditions for what games we want here
        elo = headers.get("WhiteElo")
        term = headers.get("Termination")
        elo2 = headers.get("BlackElo")
        tie = headers.get("Result") == "1/2-1/2"

        
        
        try:
            elo = int(elo)
            elo2 = int(elo2)
        except Exception as e:
            continue
        
        diff = abs(elo - elo2)


        ''' Set Conditions:
            elo > 1200 -- White Elo is higher than 1200
            term != "Time forfeit" check game does not end by time (People leave etc)
            elo2 > 1200 -- Black Elo is higher than 1200
            dif < 200 -- check elo difference is less than 200
            not tie -- check game ends with victor
        '''
        if (elo > 1200 and term != "Time forfeit" and elo2 > 1200 and diff < 200 and not tie):
            game_locations.append(game_location)

        i += 1
            
    # Loop through our games
    return game_locations

def process_games(locations: List[int], infile: str = "data/lichess_db_standard_rated_2013-01.pgn", outfile: str = 'output.txt', evaluation: bool = False) -> None:
    
    pgn = open(infile)
    
    f = open(outfile, 'w')
    f.close()
    engine = None
    GET_EVAL = evaluation
    
    if (GET_EVAL == True):
        path = Path(__file__).parents[3] / 'stockfish/stockfish_15_x64'
        engine = chess.engine.SimpleEngine.popen_uci(str(path.absolute()))
    
    # Location of the game
    for location in locations:
        board = None
        pgn.seek(location)
        game = chess.pgn.read_game(pgn)
        nodes = game.mainline()
        
        # Find a good position in this game to analyze
        i = 0
        board = game.board()
        for position in nodes:
            if (not board.is_capture(position.move) and i > 30):
                break;
            # Next position
            board = position.board()
            i += 1
        
        if (not board):
            continue
        
        fen = board.fen()
        
        score = 0
        if (GET_EVAL == True):
            analysis = engine.analyse(board, chess.engine.Limit(depth=12)) # Change depth or time=1 to set how long it takes to run this
            # 4 mins for 200 games on depth=17
            score = analysis["score"].white()
            #score = score.wdl(model='sf').expectation()
        
        
        # Calculate moves
        moves = []
        for attacker in chess.SquareSet((board.occupied)):
            attacker_name = chess.square_name(attacker)
            for target in board.attacks(attacker):
                target_name = chess.square_name(target)
                moves.append(attacker_name+target_name)
                
                
        #whiteMoves = list(board.pseudo_legal_moves) # Or board.legal_moves if we want to limit moves when there is a check.
        #board.turn = chess.BLACK
        #blackMoves = list(board.pseudo_legal_moves)
        
        #moves = whiteMoves + blackMoves
        
        f = open(outfile, 'a')
        if (score.is_mate()):
            score = "0"
            continue
        
        f.write(fen + ",")
        
            
        
        for move in moves:
            f.write(str(move) + ",")
        f.write(str(score) + "\n")
        
        f.close()
    
    if engine:
        engine.quit()
    
if __name__ == '__main__':
    
    parser = argparse.ArgumentParser(description='Preprocess our pgn file, returns fen, legal moves, and score from whites pov')
    default_in = Path(__file__).parents[2] / 'tests/data/test.pgn'
    default_out = Path(__file__).parents[2] / 'tests/data/preprocessed.txt'
    parser.add_argument('--infile', type=str, default=default_in)
    parser.add_argument('--outfile', type=str, default=default_out)
    parser.add_argument('--evaluation', action=argparse.BooleanOptionalAction)
    
    args = (parser.parse_args())
    
    
    games = select_games(args.infile)
    
    process_games(games, args.infile, args.outfile, evaluation = args.evaluation)

