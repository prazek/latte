
// Generated from Latte.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  LatteParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    COMMENT = 39, MULTICOMMENT = 40, INT = 41, ID = 42, WS = 43, STR = 44
  };

  enum {
    RuleProgram = 0, RuleTopDef = 1, RuleClassItem = 2, RuleArg = 3, RuleBlock = 4, 
    RuleStmt = 5, RuleType_ = 6, RuleItem = 7, RuleExpr = 8, RuleAddOp = 9, 
    RuleMulOp = 10, RuleRelOp = 11
  };

  LatteParser(antlr4::TokenStream *input);
  ~LatteParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class TopDefContext;
  class ClassItemContext;
  class ArgContext;
  class BlockContext;
  class StmtContext;
  class Type_Context;
  class ItemContext;
  class ExprContext;
  class AddOpContext;
  class MulOpContext;
  class RelOpContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TopDefContext *> topDef();
    TopDefContext* topDef(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  TopDefContext : public antlr4::ParserRuleContext {
  public:
    TopDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TopDefContext() : antlr4::ParserRuleContext() { }
    void copyFrom(TopDefContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ClassDefContext : public TopDefContext {
  public:
    ClassDefContext(TopDefContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<ClassItemContext *> classItem();
    ClassItemContext* classItem(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncDefContext : public TopDefContext {
  public:
    FuncDefContext(TopDefContext *ctx);

    Type_Context *type_();
    antlr4::tree::TerminalNode *ID();
    BlockContext *block();
    ArgContext *arg();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TopDefContext* topDef();

  class  ClassItemContext : public antlr4::ParserRuleContext {
  public:
    ClassItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ClassItemContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ClassItemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FieldDeclContext : public ClassItemContext {
  public:
    FieldDeclContext(ClassItemContext *ctx);

    Type_Context *type_();
    antlr4::tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ClassItemContext* classItem();

  class  ArgContext : public antlr4::ParserRuleContext {
  public:
    ArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_Context *> type_();
    Type_Context* type_(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgContext* arg();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StmtContext() : antlr4::ParserRuleContext() { }
    void copyFrom(StmtContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AssContext : public StmtContext {
  public:
    AssContext(StmtContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DecrContext : public StmtContext {
  public:
    DecrContext(StmtContext *ctx);

    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RetContext : public StmtContext {
  public:
    RetContext(StmtContext *ctx);

    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EmptyContext : public StmtContext {
  public:
    EmptyContext(StmtContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CondContext : public StmtContext {
  public:
    CondContext(StmtContext *ctx);

    ExprContext *expr();
    StmtContext *stmt();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CondElseContext : public StmtContext {
  public:
    CondElseContext(StmtContext *ctx);

    ExprContext *expr();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VRetContext : public StmtContext {
  public:
    VRetContext(StmtContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IncrContext : public StmtContext {
  public:
    IncrContext(StmtContext *ctx);

    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStmtContext : public StmtContext {
  public:
    BlockStmtContext(StmtContext *ctx);

    BlockContext *block();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DeclContext : public StmtContext {
  public:
    DeclContext(StmtContext *ctx);

    Type_Context *type_();
    std::vector<ItemContext *> item();
    ItemContext* item(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileContext : public StmtContext {
  public:
    WhileContext(StmtContext *ctx);

    ExprContext *expr();
    StmtContext *stmt();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SExpContext : public StmtContext {
  public:
    SExpContext(StmtContext *ctx);

    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StmtContext* stmt();

  class  Type_Context : public antlr4::ParserRuleContext {
  public:
    Type_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Type_Context() : antlr4::ParserRuleContext() { }
    void copyFrom(Type_Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StrContext : public Type_Context {
  public:
    StrContext(Type_Context *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoolContext : public Type_Context {
  public:
    BoolContext(Type_Context *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassNameContext : public Type_Context {
  public:
    ClassNameContext(Type_Context *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VoidContext : public Type_Context {
  public:
    VoidContext(Type_Context *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntContext : public Type_Context {
  public:
    IntContext(Type_Context *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Type_Context* type_();

  class  ItemContext : public antlr4::ParserRuleContext {
  public:
    ItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ItemContext* item();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EIdContext : public ExprContext {
  public:
    EIdContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EFunCallContext : public ExprContext {
  public:
    EFunCallContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ERelOpContext : public ExprContext {
  public:
    ERelOpContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    RelOpContext *relOp();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ETrueContext : public ExprContext {
  public:
    ETrueContext(ExprContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EOrContext : public ExprContext {
  public:
    EOrContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EIntContext : public ExprContext {
  public:
    EIntContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *INT();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EMemberExprContext : public ExprContext {
  public:
    EMemberExprContext(ExprContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EUnOpContext : public ExprContext {
  public:
    EUnOpContext(ExprContext *ctx);

    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EStrContext : public ExprContext {
  public:
    EStrContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *STR();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ENewExprContext : public ExprContext {
  public:
    ENewExprContext(ExprContext *ctx);

    Type_Context *type_();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EMulOpContext : public ExprContext {
  public:
    EMulOpContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    MulOpContext *mulOp();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EAndContext : public ExprContext {
  public:
    EAndContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EClassCastContext : public ExprContext {
  public:
    EClassCastContext(ExprContext *ctx);

    Type_Context *type_();
    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EParenContext : public ExprContext {
  public:
    EParenContext(ExprContext *ctx);

    ExprContext *expr();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EFalseContext : public ExprContext {
  public:
    EFalseContext(ExprContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EAddOpContext : public ExprContext {
  public:
    EAddOpContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    AddOpContext *addOp();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ENullContext : public ExprContext {
  public:
    ENullContext(ExprContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  AddOpContext : public antlr4::ParserRuleContext {
  public:
    AddOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddOpContext* addOp();

  class  MulOpContext : public antlr4::ParserRuleContext {
  public:
    MulOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulOpContext* mulOp();

  class  RelOpContext : public antlr4::ParserRuleContext {
  public:
    RelOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelOpContext* relOp();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

