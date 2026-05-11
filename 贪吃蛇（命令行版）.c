//✅已审核！
/* 头文件导入————————————————————————————————*/
#include <stdio.h>      // 标准输入输出，包含printf、scanf等。
#include <stdlib.h>     // 标准库，包含system、rand、srand等。
#include <conio.h>      // 控制台输入输出，包含_kbhit、_getch等。
#include <windows.h>    // Windows API，用于控制台操作（设置光标、颜色等）。
#include <time.h>       // 时间函数，time用于随机数种子。
#include <stdbool.h>    // 布尔类型，true/false。
/*
    这是头文件，我们可以理解为导入一些要用到的工具。
    这部分很好理解，不必过多赘述。
*/
/* ————————————————————————————————————————*/


//✅已审核！
/* 常量定义————————————————————————————————*/
#define GAME_WIDTH 100    // 游戏区域的宽度（以字符为单位，用来定义蛇的活动范围）。
#define GAME_HEIGHT 25    // 游戏区域的高度。
#define INITIAL_LENGTH 3  // 初蛇的长度。
#define INITIAL_SPEED 150 // 初始游戏速度（毫秒）。
/*
    依照惯例，我们会在代码的最前面定义一些常量。
    我们会在代码中使用这些常量来定义游戏的参数。
    这样，既能增加代码的可读性，也能在我们需要修改这些常量的值时，做到一改全改。
*/
/* ————————————————————————————————————————*/


/* 数据定义————————————————————————————————*/
//✅已审核！
// 方向枚举：
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
/*
    方向枚举对应的值：
    STOP：0。
    LEFT：1。
    RIGHT：2。
    UP：3。
    DOWN：4。
    使用枚举是为了避免直接使用数字，提高可读性。
    当然，也可以直接使用数字，但是使用枚举可以使代码更加清晰。
*/

//坐标。
typedef struct {
    int x;
    int y;
} Point;
/*
    用来表示一个二维坐标点（x,y），用于定位蛇身、食物等元素。
*/

// 蛇结构体。
typedef struct {
    Point body[GAME_WIDTH*GAME_HEIGHT]; // 蛇身坐标数组。最大长度为整个游戏区域格子数。
    int length;                 // 蛇的长度。
    enum Direction dir;         // 当前方向。
    enum Direction nextDir;     // 下一个方向。
} Snake;
/*
    用来表示一个蛇的结构体。
    body：一个二维数组，用来存储蛇身的坐标。最大容量为整个游戏区域，确保蛇最长时也能存储。
    length：蛇的当前长度。
    dir：蛇当前移动方向。
    nextDir：下一次移动时的方向（用于处理输入缓冲，防止瞬间反向）。
*/

// 食物结构体：
typedef struct {
    int x;     // 食物X坐标。
    int y;     // 食物Y坐标。   
    bool eaten;// 是否被吃掉。
} Food;

// 游戏状态结构体：
typedef struct {
    Snake snake;// 蛇结构体变量。
    Food food;// 食物结构体变量。
    bool gameOver;// 游戏是否结束。
    int score;//当前游戏得分。
    int speed;// 当前游戏速度（毫秒）。
    int highScore;// 最高得分。
    int oldTailX;// 旧蛇尾位置X坐标。
    int oldTailY;// 旧蛇尾位置Y坐标。
    bool boost;// 是否长按加速。
} Game;
/* ————————————————————————————————————————*/
/*
    一般我们会在代码的前面定义一些常量、结构体、枚举等。
    这样做的好处是：
        1. 增加代码的可读性。
        2. 方便在需要时修改这些值。
    很多初学者可能对枚举enum类型和结构体struct类型不了解。

    我在这里给出一个通俗一点的解释，枚举我们可以理解为 为0、1、2、3...这样的数值取别名，
    比如 enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN }; 中，
    我们将0、1、2、3、4分别取别名为STOP、LEFT、RIGHT、UP、DOWN。
    在第55行代码中，我们使用了枚举enum Direction来定义蛇的移动方向。
    enum Direction dir; 中的dir是一个变量，它的类型是enum Direction。
    很多初学者在看到enum Direction这个类型时可能会一蒙，怎么这个数据类型有两个单词。
    数据类型不是应该像int、float这样的一个单词吗？
    我们可以直接把enum Direction看成一个整体即可。
    
    在C语言中，我们经常会使用结构体来组织不同类型的数据。
    我们可以把结构体理解为数据包，它可以把很多类型的数据包在一起，形成一个整体。
    比如我们在第44行代码中定义了一个结构体Point，它里面包了两个变量，分别是x和y。
    这样，当我们想要表示一个坐标时，就不需要单独定义两个int变量，而是直接使用一个Point类型的变量，
它内部自带x和y，用起来非常方便。

    为了使代码更加简洁，我们在定义结构体时一般会配合typedef关键字，
    比如我们在第44行代码中定义了一个结构体Point，
    我们使用typedef struct { int x; int y; } Point;来定义它。
    typedef关键字会把struct { int x; int y; } 这个整体取别名为Point。
    这样，我们在后续代码中就可以直接使用Point来表示一个坐标点，而不需要每次都写struct Point。
*/


/* 函数声明————————————————————————————————*/
void setColor(int color);//✅已审核！
void showStartScreen();// 显示开始界面。//✅已审核！
void loadHighScore(Game *game);// 加载最高得分。//✅已审核！
void initGame(Game *game);// 初始化游戏状态。//✅已审核！
void hideCursor();//✅已审核！
void gotoxy(int x, int y);//✅已审核！
void drawBorder();//✅已审核！
void drawInfo(Game* game);// 绘制游戏信息。//✅已审核！
void processInput(Game* game);// 处理用户输入。//✅已审核！
void generateFood(Game* game);//食物生成逻辑。✅已审核！
void drawGame(Game* game);//绘制蛇和食物。✅已审核！
void updateGame(Game* game);
void saveHighScore(Game* game);// 保存最高得分。✅已审核！
void checkBoost(Game* game);// 检查是否长按加速键。✅已审核！
void showCursor();//✅已审核！
void showGameOver(Game* game);// 显示游戏结束界面。//✅已审核！
/* ————————————————————————————————————————*/
/*
    我们一般会在main()函数之前写上函数的声明，这样可以提升代码的可读性。
    可以做到即使没有看到主函数的逻辑，也能知道这个游戏会有哪些功能。
    我本人喜欢这种写法。当然也有很多人会把函数的定义在main()函数的前面，
    这是一种传统的写法，但是我个人不喜欢。
    因为我认为函数的定义应该放在main()函数的后面，
    这样可以使代码更加清晰，方便阅读和维护。
*/


/* 主函数————————————————————————————————*/
int main(){
/*
    我们在看一个项目时可以直接先看主函数，其他函数依照main()函数对其的调用顺序查看。
*/

//窗口设置：
    // 窗口标题设置。//✅已审核！
    system("title 贪吃蛇游戏（命令行版）");
    /* 
        这里调用了system()函数来设置命令行的窗口标题。
        我们只需要知道如果要修改窗口标题，只需要修改"title 贪吃蛇游戏（命令行版）"中的中文内容即可。
        这行代码很简单，不必深究。
    */

    // 窗口大小设置：//✅已审核！
    char modeCommand[100];// 用于存储设置窗口大小的命令字符串。
    sprintf(modeCommand, "mode con cols=%d lines=%d", //这是在构建命令行。
            GAME_WIDTH+50, 
            GAME_HEIGHT+15);// 设置窗口大小为游戏区域宽度+50，高度+15。
    system(modeCommand);
    /* 
        这块代码初学者不需要太深究，
        只需要知道我们可以根据需要，修改代码开头定义的GAME_WIDTH和GAME_HEIGHT宏来调整窗口大小。
    */

//初始化游戏状态：
    // 定义游戏状态变量game。
    Game game;//✅已审核！
    /* 
        Game是结构体类型，里面定义了一些变量。
        因为我们在定义它时已经用了typedef关键字取了别名，所以可以直接用Game来定义变量game。
        否则将会使用struct Game game;来定义变量game。
    */

    // 加载最高分。
    loadHighScore(&game);//✅已审核！
    /* 
        这个函数的作用是读取snake_highscore.txt文件中的最高分，
    并将其存储到game这个数据包的highScore字段中。
        如果文件打开失败，将最高分设为0。
        我们可以看到，我们在调用loadHighScore()函数时，传递了&game作为参数。
        &game表示game这个数据包（结构体变量）的地址（地址可以理解为这个变量的身份证）。
        我们传入的是game这个数据包的地址&game，而不是game。
    这是因为我们在loadHighScore()函数中需要修改game这个数据包的highScore字段。
    如果我们传入的是game变量，函数内部将会对game变量进行拷贝，然后对拷贝的同名变量操作。
    对同名变量的操作不会影响到主函数中的game变量。那么在loadHighScore()函数中对highScore字段的修改就不会影响到主函数中的game变量。
        所以我们传入的是game这个数据包的地址&game，这样就可以实现在 函数内修改函数外部数据的目的。
    */

    // 初始化游戏状态。
    initGame(&game);//✅已审核！
    /*
        这个函数的作用是初始化游戏状态，将游戏状态变量game中的字段设置为初始值。
        这个函数的本质就是一推的赋值语句，我们不必深究。
    */

//绘制游戏场景：
    // 隐藏光标。
    hideCursor();//✅已审核！
    /* 
        为了使游戏界面更加干净，我们隐藏了光标。
        这是因为光标在游戏中没有实际的作用，只是为了方便用户操作。
    隐藏光标可以使游戏界面更加简洁，用户体验更好。
        这个函数我们使用了Windows API函数SetConsoleCursorInfo()来实现，我们不必深究。
     我们可以把这个函数收藏起来，因为它具有一定的通用性，
     我们可以在其他项目中使用它来隐藏光标。
    */
    
    // 输出提示信息：//✅已审核！
    showStartScreen();
    /* 
        这个函数的作用是显示开始界面，提示游戏基本信息。本质就是一推的printf语句。
        用来告诉玩家一些关于游戏的基本信息（游戏名称、玩法、得分规则等）。
        这是写命令行程序的通用步骤，我们在每个项目中都需要这样做，即使这不是强制的。
        我们不需要在这个函数上花太多时间。
    */

    system("cls");// 清屏。//✅已审核！
    /* 
        清屏可以使游戏界面更加干净，用户体验更好。
        它会清除当前屏幕上的所有内容（主要是指showStartScreen()函数输出的内容）。
    */
    
    drawBorder();// 绘制游戏边框。//✅已审核！
    /* 
        绘制游戏边框可以使游戏界面更加清晰，用户体验更好。
     它会在游戏区域的四周绘制一个边框，用于分隔游戏区域和游戏信息。
        这个函数我们调用了gotoxy()光标定位函数来实现。
        这个函数很简单，在此不多做赘述。
        我们可以把这个函数收藏起来，因为它具有一定的通用性，
     我们可以在其他项目中使用它来绘制游戏边框。
    */
    
    drawInfo(&game);// 绘制游戏信息。//✅已审核！
    /* 
        绘制游戏信息可以使游戏界面更加清晰，用户体验更好。
     它会在游戏区域的右边绘制游戏信息，包括当前得分、最高得分、游戏状态等。
        这个函数我们调用了gotoxy()光标定位函数来实现。
        这个函数很简单，在此不多做赘述。
    */
            
// 游戏主循环：
    /* 
     上面的一系列设置都是在布置游戏场景，是“静”的，
     下面的游戏主循环是游戏的核心部分。它是用来实现”动”的。
    */
    while (!game.gameOver) {// 如果game变量的gameOver字段为false，游戏一直循环。
        processInput(&game);// 处理用户按键（方向、暂停、加速等）。

        //更新：
        updateGame(&game);// 更新游戏逻辑（移动蛇、判断吃食物、碰撞检测）。
        if (!game.gameOver) {//更新画面。
            drawGame(&game);// 绘制蛇和食物。//✅已审核！
            drawInfo(&game);// 更新右侧信息栏（得分、蛇长、加速状态等）。//✅已审核！
        }
        
        checkBoost(&game);//检测方向键/WASD是否长按，设置加速标志。
        
        // 根据加速标志决定睡眠时间（加速时速度加倍，即延时减半）。
        int sleepTime = game.boost ? (game.speed / 2) : game.speed;
        if (sleepTime < 10) sleepTime = 10; // 最小10ms，防止卡死或过快。
        Sleep(sleepTime);//在游戏中使用这个函数来控制游戏时间。
    }
    // 当游戏结束时，跳出循环。
    saveHighScore(&game);// 保存最高分。//✅已审核！
    showCursor();// 把隐藏的光标又显示出来。//✅已审核！
    
    showGameOver(&game);// 打印游戏结束界面。//✅已审核！
    
    _getch();
    
    return 0;
}
/* ————————————————————————————————————————*/


/* 函数实现—————————————————————————————————*/
// 设置文本颜色（被 showStartScreen、drawBorder 等调用），这个函数不需要深究，可以收藏起来。
void setColor(int color) {//✅已审核！
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 显示开始界面:
void showStartScreen() {//✅已审核！
    system("cls");// 清除屏幕。
    
    setColor(14);// 设置下面的文本颜色为 黄色。
    printf("\n\n");
    printf("    ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗\n");
    printf("    ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝\n");
    printf("    ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  \n");
    printf("    ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  \n");
    printf("    ███████║██║ ╚████║██║  ██║██║  ██╗███████╗\n");
    printf("    ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝\n\n");
    
    setColor(11);// 设置下面的文本颜色为 青色。
    printf("             贪吃蛇游戏（命令行版）\n\n");
    
    setColor(7);// 设置下面的文本颜色为 白色。
    printf("游戏规则:\n");
    printf("    1. 使用方向键或WASD控制蛇的移动\n");
    printf("    2. 吃到★可以增加长度和得分\n");
    printf("    3. 撞到墙壁或自己身体游戏结束\n");
    printf("    4. 按住方向键/WASD可以临时加速\n");
    printf("    5. 按P键暂停，X键退出，+/-键调整基础速度\n\n");
    printf("游戏区域: %d x %d\n\n", GAME_WIDTH, GAME_HEIGHT);
    
    setColor(10);// 设置文本颜色为绿色。
    printf("按任意键开始游戏......");

    _getch();// 暂停一下，等待用户按键。
}

void loadHighScore(Game* game) {//✅已审核！
    FILE* file = fopen("snake_highscore.txt", "r");// 打开文件用于读取。
    /*
        我们声明了一个变量file，这个变量的类型是FILE*，
    FILE*表示file变量将会用来存储一个FILE类型的指针（地址），
    fopen()函数以只读的形式打开文件"snake_highscore.txt"，
    如果文件打开成功，fopen()函数就会返回一个FILE类型的指针（地址），
    并将这个指针赋值给file变量。
    */
    if (file != NULL) {// 如果file不为NULL，说明文件打开成功。
        fscanf(file, "%d", &((*game).highScore));// 从文件中读取最高分。
        /*
            我们调用了fscanf()函数，来从文件里读取数据，
            它的第一个参数是FILE类型的地址，即file变量的值。
            第二个参数是"%d"，表示要读取一个整数。
            第三个参数是 &((*game).highScore)，程序会从内到外处理，先处理*game，
        这里的*game是对game变量进行解引。即通过其值&game”链接“到外部的game变量。
        再处理.highScore，表示game变量的highScore成员，
        最后处理&，表示取地址运算符，对game这个结构体里面的highScore成员取地址，
            这条语句表示将从file这个地址读取到的整数赋值给&((*game).highScore这个地址代表的变量。
        */
        fclose(file);// 关闭文件。
    } else {
        (*game).highScore = 0;// 如果文件打开失败，将最高分设为0。
    }
}

void initGame(Game *game) {//✅已审核！
    game->snake.length = INITIAL_LENGTH;// 初始化蛇的长度为初始值，INITIAL_LENGTH已在代码开头定义。
    /*
        对于结构体指针（存放结构体地址的变量），我们可以使用->来快速解引用，
        比如game->snake.length就是(*game).snake.length。
    */
    game->snake.dir = RIGHT;// 初始化蛇的移动方向为向右。
    game->snake.nextDir = RIGHT;// 初始化蛇的下一个移动方向为向右。
        
    for (int i = 0; i < game->snake.length; i++) {
        game->snake.body[i].x = (GAME_WIDTH/2) - i;// 初始化蛇的身体坐标，从初始位置向左移动。
        game->snake.body[i].y = (GAME_HEIGHT/2);// 初始化蛇的身体坐标，Y坐标保持不变。
    }
    /*
        我们在这里使用了循环来赋值。game结构体下的snake本身就是一个结构体，
    snake结构体下的body变量是一个数组，这个数组的长度是GAME_WIDTH*GAME_HEIGHT。
    body数组的每一个值都是Point类型，即蛇身每个节点的坐标点。
        蛇当前长度为game->snake.length = INITIAL_LENGTH，INITIAL_LENGTH宏的值是3。
    我们遍历每一个节点，将其坐标赋值为初始位置向左移动的坐标。
        比如初始位置是(10,10)，那么蛇的身体坐标就会是(10,10),(9,10),(8,10)，
    上面的i表示蛇的身体长度，从0开始，所以(i=0)时，x坐标就是(10-0=10)，
    当(i=1)时，x坐标就是(10-1=9)，以此类推。
    */
    
    game->food.eaten = true;// 初始化食物状态为已被吃。
    game->gameOver = false;// 初始化游戏状态为未结束。
    game->score = 0;// 初始化得分设为0。
    game->speed = INITIAL_SPEED;// 初始化速度为初始值。
    game->oldTailX = -1;// 初始化旧尾坐标X设为-1。
    game->oldTailY = -1;// 初始化旧尾坐标Y设为-1。  
    game->boost = false;//初始化加速标志。
}

void hideCursor() {//✅已审核！
    CONSOLE_CURSOR_INFO cursor_info = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 设置光标位置（被 drawBorder、drawInfo、generateFood、drawGame 等调用），
// 这个函数的作用是将光标移动到指定的坐标位置。可以收藏起来。
void gotoxy(int x, int y) {//✅已审核！
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBorder() {//✅已审核！
    setColor(11); // 设置下面的输出均为青色，实现青色边框。
    
    // 绘制上边框。
    gotoxy(0, 0);//把光标移动到(0,0)位置。
    for (int i = 0; i<GAME_WIDTH+2; i++) {
        printf("■");
    }

    // 绘制下边框。
    gotoxy(0, GAME_HEIGHT+1);//把光标移动到(GAME_HEIGHT+1,0)位置。
    for (int i = 0; i < GAME_WIDTH + 2; i++) {
        printf("■");
    }
    
    // 绘制左右边框。
    for (int i = 1; i <= GAME_HEIGHT; i++) {
        gotoxy(0, i);//把光标移动到(0,i)位置。
        printf("■");

        gotoxy((GAME_WIDTH + 1), i);//把光标移动到(GAME_WIDTH+1,i)位置。    
        printf("■");
    }

    setColor(7);
}

// 显示游戏信息。
void drawInfo(Game *game) {//✅已审核！
    int infoStartX = GAME_WIDTH + 5;
    
    setColor(14);
    gotoxy(infoStartX, 2);
    printf("贪吃蛇游戏");
    
    gotoxy(infoStartX, 4);
    printf("当前得分: %d", game->score);
    
    gotoxy(infoStartX, 5);
    printf("最高得分: %d", game->highScore);
    
    gotoxy(infoStartX, 6);
    printf("蛇长: %d", game->snake.length);
    
    gotoxy(infoStartX, 7);
    printf("基础速度: %d", 310 - game->speed);
    
    gotoxy(infoStartX, 8);
    printf("加速状态: %s", game->boost ? "是 (2倍速)" : "否");
    /*
        我们在这里使用了三元运算符来判断加速状态。
        如果game->boost为true，那么就输出"是 (2倍速)"，否则输出"否"。
        当然，如果觉得三元运算符不够清晰，也可以使用if-else语句来实现：
            if (game->boost) {
                printf("加速状态: 是 (2倍速)");
            } else {
                printf("加速状态: 否");
            }
    */
    
    gotoxy(infoStartX, 10);
    printf("控制说明:");
    
    gotoxy(infoStartX, 11);
    printf("    ↑↓←→ 或 WASD");
    gotoxy(infoStartX, 12);
    printf("    按住方向键 - 临时加速");
    gotoxy(infoStartX, 13);
    printf("    P - 暂停游戏");
    gotoxy(infoStartX, 14);
    printf("    + - 加快基础速度");
    gotoxy(infoStartX, 15);
    printf("    - - 减慢基础速度");
    gotoxy(infoStartX, 16);
    printf("    X - 退出游戏");
    
    gotoxy(infoStartX, 18);
    printf("游戏状态:");
    gotoxy(infoStartX, 19);
    if (game->gameOver) {
        setColor(12);
        printf("游戏结束!");
    } else {
        setColor(10);
        printf("游戏中...");
    }
    
    setColor(7);
}

//按键处理：
void processInput(Game *game) {//✅已审核！
    /*
    这个函数的作用是处理用户输入。
    我们在这里使用了_getch()函数来获取用户输入的键值。
    如果用户按下了方向键，那么就根据方向键的方向来改变蛇的移动方向。
    如果用户按下了其他键，那么就根据键值来执行相应的操作。
    这个函数很好理解，不必多做解释。
    */
    if (_kbhit()) {// 如果有键盘操作。
        int key = _getch();// 获取键盘输入。
        
        if (key == 224 || key == 0) {// 如果是方向键输入。
            key = _getch();
            switch (key) {// 处理方向键输入。
                case 72: if (game->snake.dir != DOWN) game->snake.nextDir = UP; break;
                case 80: if (game->snake.dir != UP) game->snake.nextDir = DOWN; break;
                case 75: if (game->snake.dir != RIGHT) game->snake.nextDir = LEFT; break;
                case 77: if (game->snake.dir != LEFT) game->snake.nextDir = RIGHT; break;
                /*
                if (game->snake.dir != DOWN) 判断当前方向是否不是向下?用来防止直接掉头。
                只有当当前方向不是向下时，才允许将蛇的下一个方向设为向上；如果当前已经是向下，则忽略这次按键。
                其他逻辑类似。
                */
            }
        } else {// 如果是其他键输入。
            switch (key) {
                case 'w': case 'W': if (game->snake.dir != DOWN) game->snake.nextDir = UP; break;
                case 's': case 'S': if (game->snake.dir != UP) game->snake.nextDir = DOWN; break;
                case 'a': case 'A': if (game->snake.dir != RIGHT) game->snake.nextDir = LEFT; break;
                case 'd': case 'D': if (game->snake.dir != LEFT) game->snake.nextDir = RIGHT; break;
                case 'p': case 'P':{
                    int infoStartX = GAME_WIDTH + 5;
                    gotoxy(infoStartX, 21);
                    setColor(14);
                    printf("游戏暂停，按任意键继续......");
                    _getch();
                    gotoxy(infoStartX, 21);
                    printf("                       ");
                    break;
                }
                case '+': case '=':
                    if (game->speed > 50) game->speed -= 10;
                    break;
                case '-': case '_':
                    if (game->speed < 300) game->speed += 10;
                    break;
                case 'x': case 'X':
                    game->gameOver = true;
                    break;
            }
        }
    }
}

void generateFood(Game *game) {//被drawGame()函数调用。//✅已审核！
    /*
        在贪吃蛇游戏的游戏区域内随机生成一个新的食物，
    并确保食物不会出现在蛇的身体上，也不会超出游戏边界。
    生成成功后，它会将食物绘制到屏幕上。
    */
    bool valid;//用于标记当前随机生成的食物位置是否有效（即不与蛇身重叠且在边界内）。

    do {//循环生成有效坐标：
        valid = true;
        game->food.x = (rand() % GAME_WIDTH) + 1;
        game->food.y = (rand() % GAME_HEIGHT) + 1;
        /*
            (rand() % GAME_WIDTH) + 1; 生成1到GAME_WIDTH之间的随机数，
            确保食物在游戏区域内。
        */

        // 检查是否与蛇身重叠：
        for (int i = 0; i < game->snake.length; i++) {
            if (game->food.x == game->snake.body[i].x && game->food.y == game->snake.body[i].y) {
                valid = false;
                break;
            }
        }
        
        // 检查是否超出游戏边界：
        if (game->food.x <= 0 || game->food.x > GAME_WIDTH ||
            game->food.y <= 0 || game->food.y > GAME_HEIGHT) {
            valid = false;
        }

    } while (!valid);
    
    game->food.eaten = false;
    gotoxy(game->food.x, game->food.y);
    setColor(12);
    printf("★");
    setColor(7);
}

// 绘制游戏元素：
void drawGame(Game *game) {//✅已审核！
    // 擦除上一帧的蛇尾（如果有）：
    if (game->oldTailX != -1 && game->oldTailY != -1) {
        gotoxy(game->oldTailX, game->oldTailY);
        printf(" ");
    }
    // 绘制新的蛇头：
    gotoxy(game->snake.body[0].x, game->snake.body[0].y);
    setColor(10);
    printf("●");
    // 绘制蛇身：
    setColor(2);
    for (int i = 1; i < game->snake.length; i++) {
        gotoxy(game->snake.body[i].x, game->snake.body[i].y);
        printf("○");
    }
    // 如果食物已被吃，生成新食物：
    if (game->food.eaten) {
        generateFood(game);
    }
    
    setColor(7);
}

// 更新游戏逻辑：
void updateGame(Game *game) {
    /*
        这个函数是游戏的核心逻辑部分，每帧调用一次。
        它负责：
            1. 将蛇的下一个方向（由玩家输入设置）设为当前方向，实现一帧一次转向。
            2. 记录移动前的蛇尾坐标，用于后续擦除。
            3. 移动蛇身（每一节移动到前一节的位置）。
            4. 根据方向移动蛇头。
            5. 检查是否吃到食物：如果吃到，增加得分和蛇长，标记食物被吃，并可能加快速度。
            6. 检查是否撞墙或撞到自己身体，如果是则结束游戏。
    */    

    // 将下一个方向（由processInput设置）设为当前方向，实现一帧一次转向。
    game->snake.dir = game->snake.nextDir;
    
    // 记录移动前的蛇尾坐标，以便在drawGame中擦除旧的蛇尾。
    game->oldTailX = game->snake.body[game->snake.length - 1].x;
    game->oldTailY = game->snake.body[game->snake.length - 1].y;
    
    // 蛇身移动：每一节移动到前一节的位置（从尾部开始往前覆盖）。
    for (int i = game->snake.length - 1; i > 0; i--) {
        game->snake.body[i] = game->snake.body[i - 1];
    }
    
    // 根据当前方向移动蛇头。
    switch (game->snake.dir) {
        case LEFT:  game->snake.body[0].x--; break;
        case RIGHT: game->snake.body[0].x++; break;
        case UP:    game->snake.body[0].y--; break;
        case DOWN:  game->snake.body[0].y++; break;
    }
    
    // 检查蛇头是否与食物坐标重合（吃到食物）。
    if (game->snake.body[0].x == game->food.x && 
        game->snake.body[0].y == game->food.y) {
        
        // 得分加10，并更新最高分（如果超过当前纪录）。
        game->score += 10;
        if (game->score > game->highScore) game->highScore = game->score;
        
        // 蛇变长：增加一节，新的一节放在原来蛇尾的位置（旧蛇尾位置）。
        game->snake.length++;
        game->snake.body[game->snake.length - 1].x = game->oldTailX;
        game->snake.body[game->snake.length - 1].y = game->oldTailY;
        
        // 标记食物被吃，以便生成新食物；同时重置旧尾坐标，避免后续擦除出错。
        game->food.eaten = true;
        game->oldTailX = -1;
        game->oldTailY = -1;
        
        // 每增加50分，速度加快一点（延时减少5ms），但速度有下限（50ms）。
        if (game->score % 50 == 0 && game->speed > 50) {
            game->speed -= 5;
        }
    }
    
    // 碰撞检测：检查蛇头是否撞到墙壁（超出游戏区域）。
    if (game->snake.body[0].x <= 0 || game->snake.body[0].x > GAME_WIDTH ||
        game->snake.body[0].y <= 0 || game->snake.body[0].y > GAME_HEIGHT) {
        game->gameOver = true;
        return;
    }
    
    // 碰撞检测：检查蛇头是否撞到自己身体（从第二节开始检查）。
    for (int i = 1; i < game->snake.length; i++) {
        if (game->snake.body[0].x == game->snake.body[i].x && 
            game->snake.body[0].y == game->snake.body[i].y) {
            game->gameOver = true;
            return;
        }
    }
}

void checkBoost(Game *game) {//这个函数不必深究。✅已审核！
    // 检测方向键或WASD是否被按住（高位0x8000表示当前按下状态）。
    if (GetAsyncKeyState(VK_UP) & 0x8000 ||
        GetAsyncKeyState(VK_DOWN) & 0x8000 ||
        GetAsyncKeyState(VK_LEFT) & 0x8000 ||
        GetAsyncKeyState(VK_RIGHT) & 0x8000 ||
        GetAsyncKeyState('W') & 0x8000 ||
        GetAsyncKeyState('A') & 0x8000 ||
        GetAsyncKeyState('S') & 0x8000 ||
        GetAsyncKeyState('D') & 0x8000) {
        game->boost = true;
    } else {
        game->boost = false;
    }
}

// 保存最高分：
void saveHighScore(Game *game) {//✅已审核！
    FILE *file = fopen("snake_highscore.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", game->highScore);
        fclose(file);
    }
}

// 显示光标：
void showCursor() {//✅已审核！
    CONSOLE_CURSOR_INFO cursor_info = {100, TRUE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void showGameOver(Game *game) {//✅已审核！
    system("cls");

    setColor(12);
    printf("\n\n");
    printf("    ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ \n");
    printf("    ██╔══██╗██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
    printf("    ██████╔╝███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n");
    printf("    ██╔═══╝ ██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
    printf("    ██║     ██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
    printf("    ╚═╝     ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n\n");
    
    setColor(14);
    printf("                         最终得分: %d\n", game->score);
    printf("                         最高纪录: %d\n\n", game->highScore);
}