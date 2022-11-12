import chess
import sys

# Legal moves from FEN
def main(fen: str, outFile: str):
    board = chess.Board(fen)
    moves = list(board.legal_moves)
    f = open(outFile, 'w')

    for move in moves:
        f.write(str(move) + "\n")
    return


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])


