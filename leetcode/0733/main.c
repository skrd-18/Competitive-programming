#include "/home/shankar/Shiva/Competitive-programming/header-files/common.h"

void checkImage(int **image, int row, int col, int r, int c, int value, int newColor)
{
    if (r < 0 || r >= row || c < 0 || c >= col || image[r][c] == newColor || image[r][c] != value)
        return;
    image[r][c] = newColor;
    checkImage(image, row, col, r + 1, c, value, newColor);
    checkImage(image, row, col, r - 1, c, value, newColor);
    checkImage(image, row, col, r, c + 1, value, newColor);
    checkImage(image, row, col, r, c - 1, value, newColor);
}

int **floodFill(int **image, int imageSize, int *imageColSize, int sr, int sc, int newColor, int *returnSize, int **returnColumnSizes)
{
    checkImage(image, imageSize, *imageColSize, sr, sc, image[sr][sc], newColor);
    *returnSize = imageSize;
    *returnColumnSizes = (int *)malloc(imageSize * sizeof(int));
    for (int i = 0; i < imageSize; i++)
        (*returnColumnSizes)[i] = *imageColSize;
    return image;
}

int main(int argc, char const *argv[])
{
    int image[3][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    int imageSize = 3;
    int imageColSize[3] = {3, 3, 3};
    static const int sr = 1;
    static const int sc = 1;
    static const int color = 2;

    int returnSize;
    int *returnColumnSizes = (int *)malloc(imageSize * sizeof(int));
    for (int i = 0; i < imageSize; i += 1)
    {
        returnColumnSizes[i] = 1;
    }

    int **actual = floodFill((int **)image, imageSize, imageColSize, sr, sc, color, &returnSize, returnColumnSizes);

    // print actual
    for (int i = 0; i < imageSize; i++)
    {
        for (int j = 0; j < imageColSize[i]; j++)
            printf("%d ", actual[i][j]);
        printf("\n");
    }

    return 0;
}
