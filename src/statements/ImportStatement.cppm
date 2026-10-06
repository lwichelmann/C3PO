//
// Created by leonw on 14.06.2026.
//

export module ast:import_statement;
import std;
import :visitor;
import :statement;

export class ImportStatement : public Statement
{
private:
    std::string m_filePath;

public:
    explicit ImportStatement(std::string filePath);
    [[nodiscard]] const std::string& getFilePath() const;
    void accept(Visitor& visitor) override;
    [[nodiscard]] std::string toString() const override;
};
