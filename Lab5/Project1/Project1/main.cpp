#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "html.h"


// 统计文件中的字符类型数量
void count_characters(const char* filepath, int* words, int* letters, int* digits, int* spaces, int* newlines, int* punctuations, int* others) {
    FILE* file = fopen(filepath, "r");// 以读取模式打开文件
    if (file == NULL) {
        perror("Error opening file");//提示打开文件失败
        exit(EXIT_FAILURE);// 退出程序。
    }

    char ch;             // 用于存储读取的单个字符。
    int in_word = 0;     //标记是否在单词中
    while ((ch = fgetc(file)) != EOF) { //读取文件
        if (isalpha((unsigned char)ch)) {//判断是不是字母
            (*letters)++;   //字母+1
            if (!in_word) { //不在单词中开始新的单词
                in_word = 1;
                (*words)++;  //单词数+1
            }
        }
        else {//不是数字
            in_word = 0;
            if (isdigit((unsigned char)ch)) {//是否是数字
                (*digits)++;
            }
            else if (isspace((unsigned char)ch)) {//是不是空白字符
                if (ch == ' ') {//++
                    (*spaces)++;
                }
                else if (ch == '\n') {
                    (*newlines)++;
                }
            }
            else if (ispunct((unsigned char)ch)) {//如果是标点符号
                (*punctuations)++;
            }
            else {
                (*others)++;
            }
        }
    }

    fclose(file);//关闭文件
}
// 将统计结果保存到文本文件中
void save_results(const char* filepath, const char* result_filepath, int words, int letters, int digits, int spaces, int newlines, int punctuations, int others) {
    FILE* result_file = fopen(result_filepath, "w");//创建文本文件
    if (result_file == NULL) {//打开失败
        perror("Error opening result file");
        exit(EXIT_FAILURE);
    }
    //写入数据
    fprintf(result_file, "File: %s\n", filepath);
    fprintf(result_file, "Words: %d\n", words);
    fprintf(result_file, "Letters: %d\n", letters);
    fprintf(result_file, "Digits: %d\n", digits);
    fprintf(result_file, "Spaces: %d\n", spaces);
    fprintf(result_file, "Newlines: %d\n", newlines);
    fprintf(result_file, "Punctuations: %d\n", punctuations);
    fprintf(result_file, "Others: %d\n", others);

    fclose(result_file);
}
//在控制台打印统计结果
void print_results(int words, int letters, int digits, int spaces, int newlines, int punctuations, int others) {
    printf("Words: %d\n", words);
    printf("Letters: %d\n", letters);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);
    printf("Newlines: %d\n", newlines);
    printf("Punctuations: %d\n", punctuations);
    printf("Others: %d\n", others);
}
//概要模式的打印
void print_summary(const char* filepath, const char* result_filepath) {
    printf("已完成“%s”文件的统计，统计结果保存在文件“%s”中！\n", filepath, result_filepath);
}

int main(int argc, char* argv[]) {
    char filepath[256];//定义文件路径
    //如果写入文件路径继续使用
    if (argc > 1) {
        strncpy(filepath, argv[1], sizeof(filepath));
    }
    else {//为输入则提示输入
        printf("请输入文件路径：");
        scanf("%255s", filepath);
    }
    //初始化
    int words = 0, letters = 0, digits = 0, spaces = 0, newlines = 0, punctuations = 0, others = 0;
    // 统计文件中的字符
    count_characters(filepath, &words, &letters, &digits, &spaces, &newlines, &punctuations, &others);

    //生成文件路径
    char result_filepath[256];
    snprintf(result_filepath, sizeof(result_filepath), "%s_stats.txt", filepath);//snprintf 会根据 size 参数限制写入的字符数，
                                                                                 // 从而防止写入的字符超出 result_filepath 的容量，可以防止缓冲区溢出
    //选择模式
    int choice;
    printf("请选择处理模式：\n");
    printf("1. 细节模式\n");
    printf("2. 概要模式\n");
    printf("请输入你的选择 (1 或 2): ");
    scanf("%d", &choice);

    if (choice == 1) {//细节模式
        save_results(filepath, result_filepath, words, letters, digits, spaces, newlines, punctuations, others);
        print_results(words, letters, digits, spaces, newlines, punctuations, others);
        printf("统计结果已保存到文件：%s\n", result_filepath);
    }
    else if (choice == 2) {//概要模式
        save_results(filepath, result_filepath, words, letters, digits, spaces, newlines, punctuations, others);
        print_summary(filepath, result_filepath);
    }
    else {//无效
        fprintf(stderr, "无效的选择，请选择 1 或 2。\n");
        return EXIT_FAILURE;
    }

    char html_filepath[256];
    snprintf(html_filepath, sizeof(html_filepath), "%s.html", result_filepath);
    generate_html(result_filepath, html_filepath);

    int mode;
    printf("请选择工作模式：\n");
    printf("1. 自动结果展示模式\n");
    printf("2. 静默结果展示模式\n");
    printf("请输入你的选择 (1 或 2): ");
    scanf("%d", &mode);

    if (mode == 1) {
        open_browser(html_filepath);
    }
    else if (mode == 2) {
        printf("已生成html文件，文件路径为：%s\n", html_filepath);
    }
    else {
        fprintf(stderr, "无效的模式，请选择 '1' 或 '2'。\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;//正常退出程序
}