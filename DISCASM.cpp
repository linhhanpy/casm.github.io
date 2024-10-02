#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <exception>

std::string AsmToSasm(const std::string& asmCode) {
    std::unordered_map<std::string, std::string> conversionDict = {
            {"%include", "����"},
            {"extern", "����"},
            {"printf", "��ӡ"},
            {"scanf", "����"},
            {"system", "����"},
            {"SECTION.data", "�����"},
            {"SECTION.text", "�����"},
            {"SECTION.bss", "Ԥ����"},
            {",", "��"},
            {".", "��"},
            {":", "��"},
            {";", "��"},
            {"$", "��"},
            {"[", "��"},
            {"]", "��"},
            {"'", "��"},
            {"0ah", "�س�"},
            {"equ", "���峣��"},
            {"db", "����"},
            {"resb", "Ԥ���ֽ�"},
            {"resw", "Ԥ����"},
            {"resd", "Ԥ��˫��"},
            {"resq", "Ԥ��˫���ȸ�����"},
            {"rest", "Ԥ����չ���ȸ�����"},
            {"global", "ȫ��"},
            {"main", "������"},
            {"mov", "��ֵ"},
            {"lea", "д��"},
            {"int", "�ж�"},
            {"jmp", "��ת"},
            {"cmp", "�Ƚ�"},
            {"je", "�����ת"},
            {"jne", "�������ת"},
            {"jg", "������ת"},
            {"jl", "С����ת"},
            {"jge", "�����ת"},
            {"jle", "С����ת"},
            {"jng", "�Ǵ�����ת"},
            {"jnl", "��С����ת"},
            {"add", "��"},
            {"sub", "��"},
            {"mul", "��"},
            {"div", "��"},
            {"pop", "��ջ"},
            {"push", "��ջ"},
            {"ret", "����"},
            {"call", "����"},
            {"rsp", "ջ��"}
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
        throw std::runtime_error("�����ļ� " + filePath + " δ�ҵ���");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("д���ļ�ʱ��������");
    }
    file << content;
}

int main() {
    std::string sourceFilePath, targetFilePath;
    std::cout << "��������Դ�ļ�>>";
    std::cin >> sourceFilePath;
    std::cout << "������Ŀ���ļ�>>";
    std::cin >> targetFilePath;

    try {
        std::string asmCode = readFile(sourceFilePath);
        std::string sasmCode = AsmToSasm(asmCode);
        writeFile(targetFilePath, sasmCode);
        std::string writtenSasmCode = readFile(targetFilePath);
        std::cout << "ת��������ݣ�" << writtenSasmCode << std::endl;

        std::cout << "ת���ɹ���" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "����" << e.what() << std::endl;
    }

    std::system("pause");
    return 0;
}
