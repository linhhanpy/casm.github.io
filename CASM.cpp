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
        throw std::runtime_error("编译失败");
    }
    std::string gccCommand = "gcc " + objFilePath + " -o " + exeFilePath;
    int result2 = std::system(gccCommand.c_str());
    if (result2!= 0) {
        throw std::runtime_error("编译失败");
    }
    std::cout << "编译完成，目标文件已生成至: " << exeFilePath << std::endl;
    return;
}

std::string SasmToAsm(const std::string& asmCode) {
    std::unordered_map<std::string, std::string> conversionDict = {
            {"导入", "%include"},
            {"声明", "extern"},
            {"打印", "puts"},
            {"，", ","},
            {"。", "."},
            {"：", ":"},
            {"；", ";"},
            {"￥", "$"},
            {"【", "["},
            {"】", "]"},
            {"“", "'"},
            {"”", "'"},
            {"回车", "0ah"},
            {"定义段", "SECTION .data"},
            {"代码段", "SECTION .text"},
            {"预留段", "SECTION .bss"},
            {"定义常量", "equ"},
            {"定义", "db"},
            {"预留字节", "resb"},
            {"预留字", "resw"},
            {"预留双字", "resd"},
            {"预留双精度浮点数", "resq"},
            {"预留扩展精度浮点数", "rest"},
            {"全局", "global"},
            {"主函数", "main"},
            {"赋值", "mov"},
            {"中断", "int"},
            {"跳转", "jmp"},
            {"比较", "cmp"},
            {"相等跳转", "je"},
            {"非相等跳转", "jne"},
            {"大于跳转", "jg"},
            {"小于跳转", "jl"},
            {"大等跳转", "jge"},
            {"小等跳转", "jle"},
            {"非大于跳转", "jng"},
            {"非小于跳转", "jnl"},
            {"加", "add"},
            {"减", "sub"},
            {"乘", "mul"},
            {"除", "div"},
            {"出栈", "pop"},
            {"进栈", "push"},
            {"返回", "ret"},
            {"调用", "call"},
            {"栈顶", "rsp"}
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
    std::string M;
    std::cout << "模式>>";
    std::cin >> M;
    std::string sourceFilePath, targetFilePath;
    std::cout << "请输入汇编源文件>>";
    std::cin >> sourceFilePath;
    std::cout << "请输入目标文件>>";
    std::cin >> targetFilePath;

    if(M == "-r"){
        try {
            std::string sasmCode = readFile(sourceFilePath);
            std::string asmCode = SasmToAsm(sasmCode);
            writeFile("asm.asm", asmCode);
            std::string writtenAsmCode = readFile("asm.asm");
            std::cout << "写入后的内容：" << writtenAsmCode << std::endl;

            std::cout << "编译成功！" << std::endl;
            assembleWithNasm("obj.obj", "asm.asm", targetFilePath);
            std::cout << "正在运行..." << std::endl;
            int result1 = std::system(targetFilePath.c_str());
            if (result1!= 0) {
                throw std::runtime_error("运行失败");
            }
        } catch (const std::exception& e) {
            std::cerr << "错误：" << e.what() << std::endl;
        }
    }
    else if(M == "-o"){
        try {
            std::string sasmCode = readFile(sourceFilePath);
            std::string asmCode = SasmToAsm(sasmCode);
            writeFile("asm.asm", asmCode);
            std::string writtenAsmCode = readFile("asm.asm");
            std::cout << "写入后的内容：" << writtenAsmCode << std::endl;

            std::cout << "编译成功！" << std::endl;
            assembleWithNasm("obj.obj", "asm.asm", targetFilePath);

        } catch (const std::exception& e) {
            std::cerr << "错误：" << e.what() << std::endl;
        }
    }
    else if(M == "-a"){
        try {
            std::string sasmCode = readFile(sourceFilePath);
            std::string asmCode = SasmToAsm(sasmCode);
            writeFile("asm.asm", asmCode);
            std::string writtenAsmCode = readFile("asm.asm");
            std::cout << "写入后的内容：" << writtenAsmCode << std::endl;

            std::cout << "编译成功！" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "错误：" << e.what() << std::endl;
        }
    }
    else {
        std::cout << "模式错误";
    }
    std::system("pause");
    return 0;
}


