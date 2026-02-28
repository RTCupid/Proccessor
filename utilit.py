import cv2
import numpy as np
import sys

width, height = 128, 128
num_frames = 6563  # для 3 мин 40 сек при 30 fps
with open('tests/bad_apple/frames.bin', 'wb') as f:
    for i in range(num_frames):
        img = cv2.imread(f'tests/bad_apple/ba_frames/frame_{i+1:04d}.png', cv2.IMREAD_GRAYSCALE)
        img = cv2.resize(img, (width, height))
        # бинаризация: порог 128
        binary = (img > 128).astype(np.int32).flatten()
        f.write(binary.tobytes())
