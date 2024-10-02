#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <exception>

std::string AsmToSasm(const std::string& asmCode) {
    std::unordered_map<std::string, std::string> conversionDict = {
            {"%include", "导入"},
            {"extern", "声明"},
            {"printf", "打印"},
            {"scanf", "输入"},
            {"system", "命令"},
            {"SECTION.data", "定义段"},
            {"SECTION.text", "代码段"},
            {"SECTION.bss", "预留段"},
            {",", "，"},
            {".", "。"},
            {":", "："},
            {";", "；"},
            {"$", "￥"},
            {"[", "【"},
            {"]", "】"},
            {"'", "“"},
            {"0ah", "回车"},
            {"equ", "定义常量"},
            {"db", "定义"},
            {"resb", "预留字节"},
            {"resw", "预留字"},
            {"resd", "预留双字"},
            {"resq", "预留双精度浮点数"},
            {"rest", "预留扩展精度浮点数"},
            {"global", "全局"},
            {"main", "主函数"},
            {"mov", "赋值"},
            {"lea", "写入"},
            {"int", "中断"},
            {"jmp", "跳转"},
            {"cmp", "比较"},
            {"je", "相等跳转"},
            {"jne", "非相等跳转"},
            {"jg", "大于跳转"},
            {"jl", "小于跳转"},
            {"jge", "大等跳转"},
            {"jle", "小等跳转"},
            {"jng", "非大于跳转"},
            {"jnl", "非小于跳转"},
            {"add", "加"},
            {"sub", "减"},
            {"mul", "乘"},
            {"div", "除"},
            {"pop", "出栈"},
            {"push", "进栈"},
            {"ret", "返回"},
            {"call", "调用"},
            {"rsp", "栈顶"}
    };
    std::string modifiedAsmCode = asmCode;
    for (const auto& pair : conversionDict) {
        size_t pos = 0;
        while ((pos = modifiedAsmCode.find(pair.first, pos))!= std::string::npos) {
            modifiedAsmCode.replace(pos, pair.first.length(), pair.second);
            pos += pair.second.length();
        }
    }
    return modifiedAsmCode;
}

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("错误：文件 " + filePath + " 未找到。");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("写入文件时发生错误");
    }
    file << content;
}

int main() {
    std::string sourceFilePath, targetFilePath;
    std::cout << "请输入汇编源文件>>";
    std::cin >> sourceFilePath;
    std::cout << "请输入目标文件>>";
    std::cin >> targetFilePath;

    try {
        std::string asmCode = readFile(sourceFilePath);
        std::string sasmCode = AsmToSasm(asmCode);
        writeFile(targetFilePath, sasmCode);
        std::string writtenSasmCode = readFile(targetFilePath);
        std::cout << "转换后的内容：" << writtenSasmCode << std::endl;

        std::cout << "转换成功！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }

    std::system("pause");
    return 0;
}
