#ifndef COMPILER_H
#define COMPILER_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct ParsedStatement
{
    std::string variable_name;
    uint8_t first_operand;
    char operator_character;
    uint8_t second_operand;
};

class Compiler
{
public:
    Compiler();

    std::vector<uint8_t> compile(const std::string& source_code);
    uint8_t get_variable_address(const std::string& variable_name) const;

private:
    static constexpr uint8_t VARIABLE_STORAGE_START = 0xC0;
    static constexpr uint8_t VARIABLE_STORAGE_SIZE = 0x20;

    ParsedStatement parse_statement(const std::string& source_code) const;
    uint8_t get_or_assign_address(const std::string& variable_name) const;
    std::vector<uint8_t> emit_bytecode(const ParsedStatement& parsed_statement) const;

    mutable std::unordered_map<std::string, uint8_t> symbol_table;
};

#endif
