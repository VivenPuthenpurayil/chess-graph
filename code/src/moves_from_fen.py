import chess
import chess.engine
import argparse
from pathlib import Path

# Legal moves from FEN, ALSO GETS EVAL
def main(fen: str, outFile: str) -> None:
    
    path = Path(__file__).parents[2] / 'stockfish/stockfish_15_x64'
    
    engine = chess.engine.SimpleEngine.popen_uci(str(path.absolute())) #chess.engine.SimpleEngine.popen_uci(str(path.absolute()))
    board = chess.Board(fen) # rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    analysis = engine.analyse(board, chess.engine.Limit(time=1))
    
    score = analysis["score"].relative
    score = score.wdl(model='sf').expectation()
    
    engine.quit()
    
    moves = list(board.legal_moves)

    # Write data to file
    f = open(outFile, 'w')
 
    for move in moves:
        f.write(str(move) + ",")
    f.write(str(score) + "\n")
    
    f.close()
    return

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert a FEN string to a list of legal moves, and a win percent for white')
    parser.add_argument('FEN', type=str)
    parser.add_argument('outfile', type=str)
    args = (parser.parse_args())
    main(args.FEN, args.outfile)


