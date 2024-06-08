#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "html.h"


// ͳ���ļ��е��ַ���������
void count_characters(const char* filepath, int* words, int* letters, int* digits, int* spaces, int* newlines, int* punctuations, int* others) {
    FILE* file = fopen(filepath, "r");// �Զ�ȡģʽ���ļ�
    if (file == NULL) {
        perror("Error opening file");//��ʾ���ļ�ʧ��
        exit(EXIT_FAILURE);// �˳�����
    }

    char ch;             // ���ڴ洢��ȡ�ĵ����ַ���
    int in_word = 0;     //����Ƿ��ڵ�����
    while ((ch = fgetc(file)) != EOF) { //��ȡ�ļ�
        if (isalpha((unsigned char)ch)) {//�ж��ǲ�����ĸ
            (*letters)++;   //��ĸ+1
            if (!in_word) { //���ڵ����п�ʼ�µĵ���
                in_word = 1;
                (*words)++;  //������+1
            }
        }
        else {//��������
            in_word = 0;
            if (isdigit((unsigned char)ch)) {//�Ƿ�������
                (*digits)++;
            }
            else if (isspace((unsigned char)ch)) {//�ǲ��ǿհ��ַ�
                if (ch == ' ') {//++
                    (*spaces)++;
                }
                else if (ch == '\n') {
                    (*newlines)++;
                }
            }
            else if (ispunct((unsigned char)ch)) {//����Ǳ�����
                (*punctuations)++;
            }
            else {
                (*others)++;
            }
        }
    }

    fclose(file);//�ر��ļ�
}
// ��ͳ�ƽ�����浽�ı��ļ���
void save_results(const char* filepath, const char* result_filepath, int words, int letters, int digits, int spaces, int newlines, int punctuations, int others) {
    FILE* result_file = fopen(result_filepath, "w");//�����ı��ļ�
    if (result_file == NULL) {//��ʧ��
        perror("Error opening result file");
        exit(EXIT_FAILURE);
    }
    //д������
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
//�ڿ���̨��ӡͳ�ƽ��
void print_results(int words, int letters, int digits, int spaces, int newlines, int punctuations, int others) {
    printf("Words: %d\n", words);
    printf("Letters: %d\n", letters);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);
    printf("Newlines: %d\n", newlines);
    printf("Punctuations: %d\n", punctuations);
    printf("Others: %d\n", others);
}
//��Ҫģʽ�Ĵ�ӡ
void print_summary(const char* filepath, const char* result_filepath) {
    printf("����ɡ�%s���ļ���ͳ�ƣ�ͳ�ƽ���������ļ���%s���У�\n", filepath, result_filepath);
}

int main(int argc, char* argv[]) {
    char filepath[256];//�����ļ�·��
    //���д���ļ�·������ʹ��
    if (argc > 1) {
        strncpy(filepath, argv[1], sizeof(filepath));
    }
    else {//Ϊ��������ʾ����
        printf("�������ļ�·����");
        scanf("%255s", filepath);
    }
    //��ʼ��
    int words = 0, letters = 0, digits = 0, spaces = 0, newlines = 0, punctuations = 0, others = 0;
    // ͳ���ļ��е��ַ�
    count_characters(filepath, &words, &letters, &digits, &spaces, &newlines, &punctuations, &others);

    //�����ļ�·��
    char result_filepath[256];
    snprintf(result_filepath, sizeof(result_filepath), "%s_stats.txt", filepath);//snprintf ����� size ��������д����ַ�����
                                                                                 // �Ӷ���ֹд����ַ����� result_filepath �����������Է�ֹ���������
    //ѡ��ģʽ
    int choice;
    printf("��ѡ����ģʽ��\n");
    printf("1. ϸ��ģʽ\n");
    printf("2. ��Ҫģʽ\n");
    printf("���������ѡ�� (1 �� 2): ");
    scanf("%d", &choice);

    if (choice == 1) {//ϸ��ģʽ
        save_results(filepath, result_filepath, words, letters, digits, spaces, newlines, punctuations, others);
        print_results(words, letters, digits, spaces, newlines, punctuations, others);
        printf("ͳ�ƽ���ѱ��浽�ļ���%s\n", result_filepath);
    }
    else if (choice == 2) {//��Ҫģʽ
        save_results(filepath, result_filepath, words, letters, digits, spaces, newlines, punctuations, others);
        print_summary(filepath, result_filepath);
    }
    else {//��Ч
        fprintf(stderr, "��Ч��ѡ����ѡ�� 1 �� 2��\n");
        return EXIT_FAILURE;
    }

    char html_filepath[256];
    snprintf(html_filepath, sizeof(html_filepath), "%s.html", result_filepath);
    generate_html(result_filepath, html_filepath);

    int mode;
    printf("��ѡ����ģʽ��\n");
    printf("1. �Զ����չʾģʽ\n");
    printf("2. ��Ĭ���չʾģʽ\n");
    printf("���������ѡ�� (1 �� 2): ");
    scanf("%d", &mode);

    if (mode == 1) {
        open_browser(html_filepath);
    }
    else if (mode == 2) {
        printf("������html�ļ����ļ�·��Ϊ��%s\n", html_filepath);
    }
    else {
        fprintf(stderr, "��Ч��ģʽ����ѡ�� '1' �� '2'��\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;//�����˳�����
}