#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html.h"
//����HTML��ʽ��ͳ�ƽ���ļ�
void generate_html(const char* input_file, const char* output_file) {
    FILE* infile = fopen(input_file, "r");
    if (infile == NULL) {
        perror("�޷��������ļ���");
        exit(EXIT_FAILURE);
    }

    FILE* outfile = fopen(output_file, "w");
    if (outfile == NULL) {
        perror("�޷�������ļ���");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    // д��HTMLͷ������ʽ
    fprintf(outfile, "<!DOCTYPE html>\n");
    fprintf(outfile, "<html lang=\"en\">\n");
    fprintf(outfile, "<head>\n");
    fprintf(outfile, "    <meta charset=\"UTF-8\">\n");
    fprintf(outfile, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(outfile, "    <meta http-equiv=\"refresh\" content=\"50;url='file:///D:/Lab5/DataFile.txt_stats.txt.html'\">\n");
    fprintf(outfile, "    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n");
    fprintf(outfile, "    <link rel=\"stylesheet\" href=\"./css/style.css\">\n");
    fprintf(outfile, "</head>\n");
    fprintf(outfile, "<body>\n");

    // д��̶���HTML���ݣ�ͷ��ģ�飩
    fprintf(outfile, "    <!-- ͷ��ģ�� -->\n");
    fprintf(outfile, "    <div class=\"header\">\n");
    fprintf(outfile, "        <div class=\"title\">\n");
    fprintf(outfile, "            <span>Lab5</span>\n");
    fprintf(outfile, "        </div>\n");
    fprintf(outfile, "        <div class=\"time\">\n");
    fprintf(outfile, "            <span></span>\n");
    fprintf(outfile, "        </div>\n");
    fprintf(outfile, "        <div class=\"company\">\n");
    fprintf(outfile, "            <span>File   </span>\n");
    fprintf(outfile, "            <span>D:\Lab5\DataFile.txt</span>\n");
    fprintf(outfile, "        </div>\n");
    fprintf(outfile, "    </div>\n");

    // д������ģ��
    fprintf(outfile, "    <!-- ����ģ�� -->\n");
    fprintf(outfile, "    <div class=\"main\">\n");
    fprintf(outfile, "        <div class=\"animate\">\n");
    fprintf(outfile, "            <!-- ������ -->\n");
    fprintf(outfile, "            <div class=\"float\">\n");



     // Floating sections
    const char* contents[] = { "Newlines: 2", "Spaces: 77", "Digits: 7", "Words: 80"};
    for (int i = 1; i <= 5; i++) {
        // ʹ�� i % 4 ��ѭ������ contents ����
        int contentIndex = i % 4;

        fprintf(outfile, "                <div class=\"floating%d\">\n", i);
        fprintf(outfile, "                    <div id=\"roate%d\">\n", i);

        // ����� i ��ѭ����Ӧ������
        fprintf(outfile, "                        <div class=\"roate-item%d\">\n", i);
        fprintf(outfile, "                            <p>%s</p>\n", contents[contentIndex]);
        fprintf(outfile, "                        </div>\n");

        fprintf(outfile, "                    </div>\n");
        fprintf(outfile, "                </div>\n");
    }
   
    //D:\Lab5\DataFile.txt
    // Sum section
    fprintf(outfile, "            </div>\n");
    fprintf(outfile, "            <div class=\"sum\">\n");
    fprintf(outfile, "                <div class=\"data\">\n");

    fprintf(outfile, "                    <span></span>\n");
    fprintf(outfile, "                </div>\n");
    fprintf(outfile, "                <div class=\"cicle1\"></div>\n");
    fprintf(outfile, "                <canvas id=\"canvas1\"></canvas>\n");
    fprintf(outfile, "                <canvas id=\"canvas2\"></canvas>\n");
    for (int i = 1; i <= 4; i++) {
        fprintf(outfile, "                <div class=\"data%d\">\n", i);
        fprintf(outfile, "                    <div class=\"qiu\">\n");
        switch (i) {
        case 1: fprintf(outfile, "                     <p>Newlines: 2</p>\n");
            break;
        case 2:fprintf(outfile, "                     <p>Punctuations: 13</p>\n");
            break;
        case 3:fprintf(outfile, "                     <p>Others: 2</p>\n");
            break;
        case 4:fprintf(outfile, "                     <p>D:\Lab5\DataFile.txt</p>\n");
            break;
        }
      
        fprintf(outfile, "                    </div>\n");
   
        fprintf(outfile, "                </div>\n");
    }

    fprintf(outfile, "            </div>\n");
    fprintf(outfile, "        </div>\n");

    // Charts section
    fprintf(outfile, "        <div class=\"charts\">\n");
    fprintf(outfile, "            <div class=\"charts1\">\n");
    fprintf(outfile, "                <div class=\"charts-title\">\n");

    fprintf(outfile, "                </div>\n");
    fprintf(outfile, "                <div class=\"charts-content1 content\"></div>\n");
    fprintf(outfile, "            </div>\n");
    fprintf(outfile, "            <div class=\"charts2\">\n");
    fprintf(outfile, "                <div class=\"charts-title\">\n");
    fprintf(outfile, "                </div>\n");
    fprintf(outfile, "                <div class=\"charts-content2 content\">\n");
    fprintf(outfile, "                    <table>\n");
    fprintf(outfile, "                        <thead>\n");
    fprintf(outfile, "                            <tr>\n");
    fprintf(outfile, "                            </tr>\n");
    fprintf(outfile, "                        </thead>\n");
    fprintf(outfile, "                        <tbody>\n");

    // �������ļ���ȡ���ݲ�д����
    char line[256];
    while (fgets(line, sizeof(line), infile)) {
        char* colon = strchr(line, ':');
        if (colon != NULL) {
            *colon = '\0';
            char* item = line;
            char* count = colon + 1;

            // ȥ��ͳ�����������ǰ��ո�
            while (*item == ' ' || *item == '\t') item++;
            while (*count == ' ' || *count == '\t') count++;
            char* end = count + strlen(count) - 1;
            while (end > count && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
                *end = '\0';
                end--;
            }

            fprintf(outfile, "                            <tr>\n");
            fprintf(outfile, "                                <td>%s</td>\n", item);
            fprintf(outfile, "                                <td>%s</td>\n", count);
            fprintf(outfile, "                            </tr>\n");
        }
    }

    fprintf(outfile, "                        </tbody>\n");
    fprintf(outfile, "                    </table>\n");
    fprintf(outfile, "                </div>\n");
    fprintf(outfile, "            </div>\n");
    fprintf(outfile, "        </div>\n");
    fprintf(outfile, "    </div>\n");
    fprintf(outfile, "</body>\n");
    fprintf(outfile, "<script src=\"./js/jquery-1.11.0.min.js\"></script>\n");
    fprintf(outfile, "<script src=\"./js/echarts.min.js\"></script>\n");
    fprintf(outfile, "<script src=\"./js/main.js\"></script>\n");
    fprintf(outfile, "</html>\n");

    fclose(infile);
    fclose(outfile);
}


//��Ĭ��������д�ָ�����ļ�
void open_browser(const char* file_path) {
    char command[256];

    // ���ݲ���ϵͳ���ͣ�������ͬ������
#ifdef _WIN64
    snprintf(command, sizeof(command), "start %s", file_path);
#elif __APPLE__
    snprintf(command, sizeof(command), "open %s", file_path);
#else
    snprintf(command, sizeof(command), "xdg-open %s", file_path);
#endif

    
    // ʹ��system����ִ������������
    int result = system(command);
    if (result == -1) {
        perror("Error opening browser");
        exit(EXIT_FAILURE);
    }
}