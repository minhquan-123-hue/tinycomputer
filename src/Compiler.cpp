#include "../lib/Compiler.h"

#include <cctype>
#include <sstream>
#include <stdexcept>

#include "../lib/Intructions.h"

Compiler::Compiler()
    : symbol_table()
{
}

std::vector<uint8_t> Compiler::compile(const std::string& source_code)
{
    ParsedStatement parsed_statement = parse_statement(source_code);
    uint8_t variable_address = get_or_assign_address(parsed_statement.variable_name);

    std::vector<uint8_t> bytecode = emit_bytecode(parsed_statement);
    bytecode.push_back(OPCODE_STORE);
    bytecode.push_back(variable_address);
    bytecode.push_back(OPCODE_HALT);
    bytecode.push_back(0x00);

    return bytecode;
}

uint8_t Compiler::get_variable_address(const std::string& variable_name) const
{
    auto iterator = symbol_table.find(variable_name);
    if (iterator == symbol_table.end())
    {
        throw std::runtime_error("unknown variable");
    }

    return iterator->second;
}

ParsedStatement Compiler::parse_statement(const std::string& source_code) const
{
    std::string trimmed_source = source_code;
    while (!trimmed_source.empty() && std::isspace(static_cast<unsigned char>(trimmed_source.front())))
    {
        trimmed_source.erase(trimmed_source.begin());
    }
    while (!trimmed_source.empty() && std::isspace(static_cast<unsigned char>(trimmed_source.back())))
    {
        trimmed_source.pop_back();
    }

    std::size_t equals_position = trimmed_source.find('=');
    if (equals_position == std::string::npos)
    {
        throw std::runtime_error("malformed source code");
    }

    std::string variable_name = trimmed_source.substr(0, equals_position);
    std::string expression = trimmed_source.substr(equals_position + 1);

    while (!variable_name.empty() && std::isspace(static_cast<unsigned char>(variable_name.back())))
    {
        variable_name.pop_back();
    }
    while (!variable_name.empty() && std::isspace(static_cast<unsigned char>(variable_name.front())))
    {
        variable_name.erase(variable_name.begin());
    }

    while (!expression.empty() && std::isspace(static_cast<unsigned char>(expression.front())))
    {
        expression.erase(expression.begin());
    }
    while (!expression.empty() && std::isspace(static_cast<unsigned char>(expression.back())))
    {
        expression.pop_back();
    }

    if (variable_name.empty() || variable_name.size() > 16)
    {
        throw std::runtime_error("invalid variable name");
    }

    for (char character : variable_name)
    {
        if (!std::islower(static_cast<unsigned char>(character)))
        {
            throw std::runtime_error("invalid variable name");
        }
    }

    std::stringstream expression_stream(expression);
    std::string first_number_text;
    std::string operator_character_text;
    std::string second_number_text;
    if (!(expression_stream >> first_number_text >> operator_character_text >> second_number_text))
    {
        throw std::runtime_error("malformed expression");
    }

    if (operator_character_text.size() != 1 || (operator_character_text[0] != '+' && operator_character_text[0] != '-'))
    {
        throw std::runtime_error("unsupported operator");
    }

    ParsedStatement parsed_statement;
    parsed_statement.variable_name = variable_name;
    parsed_statement.first_operand = static_cast<uint8_t>(std::stoi(first_number_text));
    parsed_statement.operator_character = operator_character_text[0];
    parsed_statement.second_operand = static_cast<uint8_t>(std::stoi(second_number_text));

    return parsed_statement;
}

uint8_t Compiler::get_or_assign_address(const std::string& variable_name) const
{
    auto iterator = symbol_table.find(variable_name);
    if (iterator != symbol_table.end())
    {
        return iterator->second;
    }

    if (symbol_table.size() >= VARIABLE_STORAGE_SIZE)
    {
        throw std::runtime_error("variable storage exhausted");
    }

    uint8_t address = static_cast<uint8_t>(VARIABLE_STORAGE_START + symbol_table.size());
    symbol_table.emplace(variable_name, address);
    return address;
}

std::vector<uint8_t> Compiler::emit_bytecode(const ParsedStatement& parsed_statement) const
{
    std::vector<uint8_t> bytecode;
    bytecode.push_back(OPCODE_LOAD_IMM);
    bytecode.push_back(parsed_statement.first_operand);
    bytecode.push_back(OPCODE_MOV_A_B);
    bytecode.push_back(0x00);
    bytecode.push_back(OPCODE_LOAD_IMM);
    bytecode.push_back(parsed_statement.second_operand);

    if (parsed_statement.operator_character == '+')
    {
        bytecode.push_back(OPCODE_ADD);
    }
    else
    {
        bytecode.push_back(OPCODE_SUB);
    }

    bytecode.push_back(0x00);
    return bytecode;
}
