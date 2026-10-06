//
// Created by leonw on 14.06.2026.
//

module ast;
import std;

ImportStatement::ImportStatement(std::string filePath)
    : m_filePath(std::move(filePath))
{
}

const std::string& ImportStatement::getFilePath() const
{
    return m_filePath;
}

void ImportStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

std::string ImportStatement::toString() const
{
    return "import \"" + m_filePath + "\";";
}
