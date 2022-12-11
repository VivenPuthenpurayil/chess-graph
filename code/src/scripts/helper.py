import chess
import chess.engine
import chess.pgn
import argparse
from typing import List
from pathlib import Path

board = chess.Board() # Default fen

moves = []
for attacker in chess.SquareSet((board.occupied)):
    attacker_name = chess.square_name(attacker)
    for target in board.attacks(attacker):
        target_name = chess.square_name(target)
        moves.append(attacker_name+target_name)
        
print(moves)