#include <stdio.h>
#include <conio.h>
// basic snake game

struct snake
{
    char value;
    int x;
    int y;
};

void draw(int n, char board[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);   
        }
        printf("\n");
    }
}

void createBoundry(int n, char board[][n]){
     for(int i=0; i<n; i++){
        board[i][0] = '*';
        board[i][n-1] = '*';
    }
    for(int i=0; i<n; i++){
        board[0][i] = '*';
        board[n-1][i] = '*';
    }
}

void updateBoard(int n, char board[][n], struct snake s[], int snakeLength, struct snake fruit)
{
    int i;
    for (i = 1; i < n-1; i++)
    {
        for (int j = 1; j < n-1; j++)
        {
            board[i][j] = ' ';
        }
    }
   
    board[fruit.x][fruit.y] = '$';
    i = 0;
    while (i < snakeLength)
    {
        board[s[i].x][s[i].y] = s[i].value;
        i++;
    }
}

void boundryCollision(struct snake *h, int n)
{
    if (h->x == 0)
    {
        h->x = n - 2;
    }
    else if (h->x == n - 1)
    {
        h->x = 1;
    }
    if (h->y == 0)
    {
        h->y = n - 2;
    }
    else if (h->y == n - 1)
    {
        h->y = 1;
    }
}

void increaseLength(int *snakeLength, int newhx, int newhy, struct snake *fruit, struct snake s[], int n)
{
    s[*snakeLength - 1].value = '+';
    *snakeLength += 1;
    s[*snakeLength - 1].x = newhx;
    s[*snakeLength - 1].y = newhy;
    s[*snakeLength - 1].value = '#';
    generateFruit(fruit,s,n,*snakeLength);
}

void generateFruit(struct snake *fruit, struct snake s[], int n, int snakeLength)
{
    do
    {
        fruit->x = rand() % n;
        for(int i=0; i<snakeLength; i++){
            if(fruit->x == s[i].x){
                fruit->x = rand() % n;
            }
        }
    } while (fruit->x == 0 || fruit->x == n - 1);
    do
    {
        fruit->y = rand() % n;
    } while (fruit->y == 0 || fruit->y == n - 1);
}

int selfCollision(struct snake s[], int snakeLength)
{
    for (int i = 0; i < snakeLength - 1; i++)
    {
        if (s[i].x == s[snakeLength - 1].x && s[i].y == s[snakeLength - 1].y)
        {
            return 1;
        }
    }
    return 0;
}

int headUpdate(int n, struct snake *fruit, struct snake s[], int *snakeLength)
{
    printf("Press 'a' to  turn left, 'd' for right, 'w' to move upward, and 's' to move downward : ");
    int bx = s[*snakeLength - 2].x, by = s[*snakeLength - 2].y;
    int hx = s[*snakeLength - 1].x, hy = s[*snakeLength - 1].y;
    char direction = 'd';
    scanf(" %c", &direction);
    int i = *snakeLength - 1;
    switch (direction)
    {
    case 'a':
        if (hy - 1 != by)
        {
            s[i].y--;
            if (s[i].y == fruit->y && s[i].x == fruit->x)
            {
                int newhx = s[*snakeLength - 1].x;
                int newhy = s[*snakeLength - 1].y;
                s[i].y++;
                increaseLength(snakeLength, newhx, newhy, fruit, s, n);
                return 0;
            }
            return 1;
        }
        break;
    case 'd':
        if (hy + 1 != by)
        {
            s[i].y++;
            if (s[i].y == fruit->y && s[i].x == fruit->x)
            {
                int newhx = s[*snakeLength - 1].x;
                int newhy = s[*snakeLength - 1].y;
                s[i].y--;
                increaseLength(snakeLength, newhx, newhy, fruit, s, n);
                return 0;
            }
            return 1;
        }
        break;
    case 'w':
        if (hx - 1 != bx)
        {
            s[i].x--;
            if (s[i].y == fruit->y && s[i].x == fruit->x)
            {
                int newhx = s[*snakeLength - 1].x;
                int newhy = s[*snakeLength - 1].y;
                s[i].x++;
                increaseLength(snakeLength, newhx, newhy, fruit, s, n);
                return 0;
            }
            return 1;
        }
        break;
    case 's':
        if (hx + 1 != bx)
        {
            s[i].x++;
            if (s[i].y == fruit->y && s[i].x == fruit->x)
            {
                int newhx = s[*snakeLength - 1].x;
                int newhy = s[*snakeLength - 1].y;
                s[i].x--;
                increaseLength(snakeLength, newhx, newhy, fruit, s, n);
                return 0;
            }
            return 1;
        }
        break;
    }
    return 0;
}

int updateBody(int n, struct snake *fruit, struct snake s[], int *snakeLength)
{
    int hx = s[*snakeLength - 1].x, hy = s[*snakeLength - 1].y;
    int count = headUpdate(n, fruit, s, snakeLength);
    int i = *snakeLength - 1;

    boundryCollision(&s[i], n);
    if (count == 1)
    {
        i = 0;

        while (i < *snakeLength - 2)
        {
            s[i].x = s[i + 1].x;
            s[i].y = s[i + 1].y;
            i++;
        }
        s[i].x = hx;
        s[i].y = hy;
    }

    int selfCollide = selfCollision(s, *snakeLength);
    if (selfCollide)
    {
        return 0;
    }
    return 1;
}

int main()
{
    int n = 15;
    char board[n][n];
    struct snake s[100] = {{'@', 1, 1}, {'+', 1, 2}, {'+', 1, 3}, {'+', 1, 4}, {'#', 1, 5}};
    int snakeLength = 5;
    struct snake fruit;
    createBoundry(n, board);
    generateFruit(&fruit, s, n, snakeLength);
    updateBoard(n, board, s, snakeLength, fruit);
    draw(n, board);
    int alive;
    do
    {
        alive = updateBody(n, &fruit, s, &snakeLength);
        updateBoard(n, board, s, snakeLength, fruit);
        draw(n, board);
    } while (alive);
    printf("Game over!");
    return 0;
}
