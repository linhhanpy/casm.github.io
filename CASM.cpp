#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <exception>

void assembleWithNasm(const std::string& objFilePath, const std::string& asmFilePath, const std::string& exeFilePath) {
    std::string nasmCommand = "nasm -f win64 -o " + objFilePath + " " + asmFilePath;
    int result = std::system(nasmCommand.c_str());
    if (result!= 0) {
        throw std::runtime_error("����ʧ��");
    }
    std::string gccCommand = "gcc " + objFilePath + " -o " + exeFilePath;
    int result2 = std::system(gccCommand.c_str());
    if (result2!= 0) {
        throw std::runtime_error("����ʧ��");
    }
    std::cout << "������ɣ�Ŀ���ļ���������: " << exeFilePath << std::endl;
    return;
}

std::string SasmToAsm(const std::string& asmCode) {
    std::unordered_map<std::string, std::string> conversionDict = {
            {"����", "%include"},
            {"����", "extern"},
            {"��ӡ", "printf"},
            {"����", "scanf"},
            {"����", "system"},
            {"��", ","},
            {"��", "."},
            {"��", ":"},
            {"��", ";"},
            {"��", "$"},
            {"��", "["},
            {"��", "]"},
            {"��", "'"},
            {"��", "'"},
            {"�س�", "0ah"},
            {"�����", "SECTION .data"},
            {"db��", "SECTION .data"},
            {"�����", "SECTION .text"},
            {"Ԥ����", "SECTION .bss"},
            {"���峣��", "equ"},
            {"����", "db"},
            {"Ԥ���ֽ�", "resb"},
            {"Ԥ������", "resw"},
            {"Ԥ��˫��", "resd"},
            {"Ԥ��˫���ȸ�����", "resq"},
            {"Ԥ����չ���ȸ�����", "rest"},
            {"ȫ��", "global"},
            {"������", "main"},
            {"��ֵ", "mov"},
            {"д��", "lea"},
            {"�ж�", "int"},
            {"�Ƚ�", "cmp"},
            {"ֱ����ת", "jmp"},
            {"�����ת", "je"},
            {"�������ת", "jne"},
            {"���ھ���ת", "jg"},
            {"С�ھ���ת", "jl"},
            {"�����ת", "jge"},
            {"С����ת", "jle"},
            {"�Ǵ�����ת", "jng"},
            {"��С����ת", "jnl"},
            {"��", "add"},
            {"��", "sub"},
            {"��", "mul"},
            {"��", "div"},
            {"��ջ", "pop"},
            {"��ջ", "push"},
            {"����", "ret"},
            {"����", "call"},
            {"ջ��", "rsp"}
    };
    std::string modifiedAsmCode = asmCode; // Create a non-const copy of asmCode
    for (const auto& pair : conversionDict) {
        size_t pos = 0;
        while ((pos = modifiedAsmCode.find(pair.first, pos)) != std::string::npos) {
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
    std::string M;
    std::cout << "ģʽ>>";
    std::cin >> M;
    std::string sourceFilePath, targetFilePath;
    std::cout << "��������Դ�ļ�>>";
    std::cin >> sourceFilePath;
    std::cout << "������Ŀ���ļ�>>";
    std::cin >> targetFilePath;

    if(M == "-r"){
        try {
            std::string sasmCode = readFile(sourceFilePath);
            std::string asmCode = SasmToAsm(sasmCode);
            writeFile("asm.asm", asmCode);
            std::string writtenAsmCode = readFile("asm.asm");
            std::cout << "д�������ݣ�" << writtenAsmCode << std::endl;

            std::cout << "����ɹ���" << std::endl;
            assembleWithNasm("obj.obj", "asm.asm", targetFilePath);
            std::cout << "��������..." << std::endl;
            int result1 = std::system(targetFilePath.c_str());
            if (result1!= 0) {
                throw std::runtime_error("����ʧ��");
            }
        } catch (const std::exception& e) {
            std::cerr << "����" << e.what() << std::endl;
        }
    }
    else if(M == "-o"){
        try {
            std::string sasmCode = readFile(sourceFilePath);
            std::string asmCode = SasmToAsm(sasmCode);
            writeFile("asm.asm", asmCode);
            std::string writtenAsmCode = readFile("asm.asm");
            std::cout << "д�������ݣ�" << writtenAsmCode << std::endl;

            std::cout << "����ɹ���" << std::endl;
            assembleWithNasm("obj.obj", "asm.asm", targetFilePath);

        } catch (const std::exception& e) {
            std::cerr << "����" << e.what() << std::endl;
        }
    }
    else if(M == "-a"){
        try {
            std::string sasmCode = readFile(sourceFilePath);
            std::string asmCode = SasmToAsm(sasmCode);
            writeFile("asm.asm", asmCode);
            std::string writtenAsmCode = readFile("asm.asm");
            std::cout << "д�������ݣ�" << writtenAsmCode << std::endl;

            std::cout << "����ɹ���" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "����" << e.what() << std::endl;
        }
    }
    else {
        std::cout << "ģʽ����";
    }
    std::system("pause");
    return 0;
}


