#ifndef PARSER_H
#define PARSER_H

#include "Directive.h"
#include "Action.h"
#include "Function.h"
#include "Scanner.h"

class Parser {
  public:
    Parser(Scanner& m_scanner, QList<Directive>& directiveList,
           QMap<QString,Function>& functionMap);

  private:
    void match(TokenId tokenId);

    void functionDefinitionList();
    void functionDefinition();
    QList<QString> nameList();

    void instructionList();
    void instruction();
    void callInstruction();
    int expressionList();

/*    void returnInstruction();
    void ifInstruction();
    void whileInstruction();
    void assignInstruction();
    void blockInstruction();*/

    void saveInstruction();
    void restoreInstruction();
    void setPenColorInstruction();
    void setPenStyleInstruction();
    void setBrushColorInstruction();
    void setBrushStyleInstruction();
    void setFontInstruction();
    void setHorizontalAlignmentInstruction();
    void setVerticalAlignmentInstruction();
    void setScaleInstruction();
    void setRotateInstruction();
    void setOriginInstruction();
    void drawLineInstruction();
    void drawRectangleInstruction();
    void drawEllipseInstruction();
    void drawTextInstruction();

    void expression();
    void expressionRest();
    void andExpression();
    void andExpressionRest();
    void relationExpression();
    void relationExpressionRest();
    void termExpression();
    void termExpressionRest();
    void factorExpression();
    void factorExpressionRest();
    void prefixExpression();
    void primaryExpression();
    void pointExpression();
    void coordinateExpression(TokenId tokenId);
    void colorExpression();
    void fontExpression();
    void callExpression();

  private:
    Token m_lookAHead;
    Scanner& m_scanner;
    QMap<QString,Function>& m_functionMap;
    QList<Directive>& m_directiveList;
};

#endif // PARSER_H
