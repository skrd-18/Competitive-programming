class Solution(object):
    def floodFill(self, image, sr, sc, newColor):
        rows, cols, orig_color = len(image), len(image[0]), image[sr][sc]
        def traverse(row, col) -> None:
            if (not (0 <= row < rows and 0 <= col < cols)) or image[row][col] != orig_color:
                return
            image[row][col] = newColor
            [traverse(row + x, col + y) for (x, y) in ((0, 1), (1, 0), (0, -1), (-1, 0))]
        if orig_color != newColor:
            traverse(sr, sc)
        return image
    

# The idea is simple. Simply perform a DFS on the source cell. Continue the DFS if:

""" Next cell is within bounds.
Next cell is the same color as source cell.
There is a tricky case where the new color is the same as the original color and if the DFS is done on it, there will be an infinite loop. If new color is same as original color, there is nothing to be done and we can simply return the image.

💯 Check out https://www.techinterviewhandbook.org for more tips and tricks by me to ace your coding interview 💯 """