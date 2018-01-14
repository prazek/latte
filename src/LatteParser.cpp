
// Generated from Latte.g4 by ANTLR 4.7.1


#include "LatteVisitor.h"

#include "LatteParser.h"


using namespace antlrcpp;
using namespace antlr4;

LatteParser::LatteParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

LatteParser::~LatteParser() {
  delete _interpreter;
}

std::string LatteParser::getGrammarFileName() const {
  return "Latte.g4";
}

const std::vector<std::string>& LatteParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& LatteParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

LatteParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LatteParser::TopDefContext *> LatteParser::ProgramContext::topDef() {
  return getRuleContexts<LatteParser::TopDefContext>();
}

LatteParser::TopDefContext* LatteParser::ProgramContext::topDef(size_t i) {
  return getRuleContext<LatteParser::TopDefContext>(i);
}


size_t LatteParser::ProgramContext::getRuleIndex() const {
  return LatteParser::RuleProgram;
}

antlrcpp::Any LatteParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::ProgramContext* LatteParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, LatteParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(24);
      topDef();
      setState(27); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LatteParser::T__2)
      | (1ULL << LatteParser::T__15)
      | (1ULL << LatteParser::T__16)
      | (1ULL << LatteParser::T__17)
      | (1ULL << LatteParser::T__18)
      | (1ULL << LatteParser::ID))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TopDefContext ------------------------------------------------------------------

LatteParser::TopDefContext::TopDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::TopDefContext::getRuleIndex() const {
  return LatteParser::RuleTopDef;
}

void LatteParser::TopDefContext::copyFrom(TopDefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ClassDefContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> LatteParser::ClassDefContext::ID() {
  return getTokens(LatteParser::ID);
}

tree::TerminalNode* LatteParser::ClassDefContext::ID(size_t i) {
  return getToken(LatteParser::ID, i);
}

std::vector<LatteParser::ClassItemContext *> LatteParser::ClassDefContext::classItem() {
  return getRuleContexts<LatteParser::ClassItemContext>();
}

LatteParser::ClassItemContext* LatteParser::ClassDefContext::classItem(size_t i) {
  return getRuleContext<LatteParser::ClassItemContext>(i);
}

LatteParser::ClassDefContext::ClassDefContext(TopDefContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::ClassDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitClassDef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncDefContext ------------------------------------------------------------------

LatteParser::Type_Context* LatteParser::FuncDefContext::type_() {
  return getRuleContext<LatteParser::Type_Context>(0);
}

tree::TerminalNode* LatteParser::FuncDefContext::ID() {
  return getToken(LatteParser::ID, 0);
}

LatteParser::BlockContext* LatteParser::FuncDefContext::block() {
  return getRuleContext<LatteParser::BlockContext>(0);
}

LatteParser::ArgContext* LatteParser::FuncDefContext::arg() {
  return getRuleContext<LatteParser::ArgContext>(0);
}

LatteParser::FuncDefContext::FuncDefContext(TopDefContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}
LatteParser::TopDefContext* LatteParser::topDef() {
  TopDefContext *_localctx = _tracker.createInstance<TopDefContext>(_ctx, getState());
  enterRule(_localctx, 2, LatteParser::RuleTopDef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(52);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LatteParser::T__15:
      case LatteParser::T__16:
      case LatteParser::T__17:
      case LatteParser::T__18:
      case LatteParser::ID: {
        _localctx = dynamic_cast<TopDefContext *>(_tracker.createInstance<LatteParser::FuncDefContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(29);
        type_();
        setState(30);
        match(LatteParser::ID);
        setState(31);
        match(LatteParser::T__0);
        setState(33);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << LatteParser::T__15)
          | (1ULL << LatteParser::T__16)
          | (1ULL << LatteParser::T__17)
          | (1ULL << LatteParser::T__18)
          | (1ULL << LatteParser::ID))) != 0)) {
          setState(32);
          arg();
        }
        setState(35);
        match(LatteParser::T__1);
        setState(36);
        block();
        break;
      }

      case LatteParser::T__2: {
        _localctx = dynamic_cast<TopDefContext *>(_tracker.createInstance<LatteParser::ClassDefContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(38);
        match(LatteParser::T__2);
        setState(39);
        match(LatteParser::ID);
        setState(42);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LatteParser::T__3) {
          setState(40);
          match(LatteParser::T__3);
          setState(41);
          match(LatteParser::ID);
        }
        setState(44);
        match(LatteParser::T__4);
        setState(48);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << LatteParser::T__15)
          | (1ULL << LatteParser::T__16)
          | (1ULL << LatteParser::T__17)
          | (1ULL << LatteParser::T__18)
          | (1ULL << LatteParser::ID))) != 0)) {
          setState(45);
          classItem();
          setState(50);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(51);
        match(LatteParser::T__5);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassItemContext ------------------------------------------------------------------

LatteParser::ClassItemContext::ClassItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::ClassItemContext::getRuleIndex() const {
  return LatteParser::RuleClassItem;
}

void LatteParser::ClassItemContext::copyFrom(ClassItemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ItemMethodDefContext ------------------------------------------------------------------

LatteParser::Type_Context* LatteParser::ItemMethodDefContext::type_() {
  return getRuleContext<LatteParser::Type_Context>(0);
}

tree::TerminalNode* LatteParser::ItemMethodDefContext::ID() {
  return getToken(LatteParser::ID, 0);
}

LatteParser::BlockContext* LatteParser::ItemMethodDefContext::block() {
  return getRuleContext<LatteParser::BlockContext>(0);
}

LatteParser::ArgContext* LatteParser::ItemMethodDefContext::arg() {
  return getRuleContext<LatteParser::ArgContext>(0);
}

LatteParser::ItemMethodDefContext::ItemMethodDefContext(ClassItemContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::ItemMethodDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitItemMethodDef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ItemVarDeclContext ------------------------------------------------------------------

LatteParser::Type_Context* LatteParser::ItemVarDeclContext::type_() {
  return getRuleContext<LatteParser::Type_Context>(0);
}

std::vector<LatteParser::ItemContext *> LatteParser::ItemVarDeclContext::item() {
  return getRuleContexts<LatteParser::ItemContext>();
}

LatteParser::ItemContext* LatteParser::ItemVarDeclContext::item(size_t i) {
  return getRuleContext<LatteParser::ItemContext>(i);
}

LatteParser::ItemVarDeclContext::ItemVarDeclContext(ClassItemContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::ItemVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitItemVarDecl(this);
  else
    return visitor->visitChildren(this);
}
LatteParser::ClassItemContext* LatteParser::classItem() {
  ClassItemContext *_localctx = _tracker.createInstance<ClassItemContext>(_ctx, getState());
  enterRule(_localctx, 4, LatteParser::RuleClassItem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(74);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ClassItemContext *>(_tracker.createInstance<LatteParser::ItemVarDeclContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(54);
      type_();
      setState(55);
      item();
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LatteParser::T__6) {
        setState(56);
        match(LatteParser::T__6);
        setState(57);
        item();
        setState(62);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(63);
      match(LatteParser::T__7);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ClassItemContext *>(_tracker.createInstance<LatteParser::ItemMethodDefContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(65);
      type_();
      setState(66);
      match(LatteParser::ID);
      setState(67);
      match(LatteParser::T__0);
      setState(69);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << LatteParser::T__15)
        | (1ULL << LatteParser::T__16)
        | (1ULL << LatteParser::T__17)
        | (1ULL << LatteParser::T__18)
        | (1ULL << LatteParser::ID))) != 0)) {
        setState(68);
        arg();
      }
      setState(71);
      match(LatteParser::T__1);
      setState(72);
      block();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgContext ------------------------------------------------------------------

LatteParser::ArgContext::ArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LatteParser::Type_Context *> LatteParser::ArgContext::type_() {
  return getRuleContexts<LatteParser::Type_Context>();
}

LatteParser::Type_Context* LatteParser::ArgContext::type_(size_t i) {
  return getRuleContext<LatteParser::Type_Context>(i);
}

std::vector<tree::TerminalNode *> LatteParser::ArgContext::ID() {
  return getTokens(LatteParser::ID);
}

tree::TerminalNode* LatteParser::ArgContext::ID(size_t i) {
  return getToken(LatteParser::ID, i);
}


size_t LatteParser::ArgContext::getRuleIndex() const {
  return LatteParser::RuleArg;
}

antlrcpp::Any LatteParser::ArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitArg(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::ArgContext* LatteParser::arg() {
  ArgContext *_localctx = _tracker.createInstance<ArgContext>(_ctx, getState());
  enterRule(_localctx, 6, LatteParser::RuleArg);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    type_();
    setState(77);
    match(LatteParser::ID);
    setState(84);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LatteParser::T__6) {
      setState(78);
      match(LatteParser::T__6);
      setState(79);
      type_();
      setState(80);
      match(LatteParser::ID);
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

LatteParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LatteParser::StmtContext *> LatteParser::BlockContext::stmt() {
  return getRuleContexts<LatteParser::StmtContext>();
}

LatteParser::StmtContext* LatteParser::BlockContext::stmt(size_t i) {
  return getRuleContext<LatteParser::StmtContext>(i);
}


size_t LatteParser::BlockContext::getRuleIndex() const {
  return LatteParser::RuleBlock;
}

antlrcpp::Any LatteParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::BlockContext* LatteParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 8, LatteParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(LatteParser::T__4);
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LatteParser::T__0)
      | (1ULL << LatteParser::T__4)
      | (1ULL << LatteParser::T__7)
      | (1ULL << LatteParser::T__11)
      | (1ULL << LatteParser::T__12)
      | (1ULL << LatteParser::T__14)
      | (1ULL << LatteParser::T__15)
      | (1ULL << LatteParser::T__16)
      | (1ULL << LatteParser::T__17)
      | (1ULL << LatteParser::T__18)
      | (1ULL << LatteParser::T__19)
      | (1ULL << LatteParser::T__20)
      | (1ULL << LatteParser::T__24)
      | (1ULL << LatteParser::T__25)
      | (1ULL << LatteParser::INT)
      | (1ULL << LatteParser::ID)
      | (1ULL << LatteParser::STR))) != 0)) {
      setState(88);
      stmt();
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
    match(LatteParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

LatteParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::StmtContext::getRuleIndex() const {
  return LatteParser::RuleStmt;
}

void LatteParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AssContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::AssContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::AssContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::AssContext::AssContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::AssContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitAss(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DecrContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::DecrContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::DecrContext::DecrContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::DecrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitDecr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RetContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::RetContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::RetContext::RetContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::RetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitRet(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EmptyContext ------------------------------------------------------------------

LatteParser::EmptyContext::EmptyContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EmptyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEmpty(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CondContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::CondContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::StmtContext* LatteParser::CondContext::stmt() {
  return getRuleContext<LatteParser::StmtContext>(0);
}

LatteParser::CondContext::CondContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CondElseContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::CondElseContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

std::vector<LatteParser::StmtContext *> LatteParser::CondElseContext::stmt() {
  return getRuleContexts<LatteParser::StmtContext>();
}

LatteParser::StmtContext* LatteParser::CondElseContext::stmt(size_t i) {
  return getRuleContext<LatteParser::StmtContext>(i);
}

LatteParser::CondElseContext::CondElseContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::CondElseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitCondElse(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VRetContext ------------------------------------------------------------------

LatteParser::VRetContext::VRetContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::VRetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitVRet(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IncrContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::IncrContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::IncrContext::IncrContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::IncrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitIncr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStmtContext ------------------------------------------------------------------

LatteParser::BlockContext* LatteParser::BlockStmtContext::block() {
  return getRuleContext<LatteParser::BlockContext>(0);
}

LatteParser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::BlockStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitBlockStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeclContext ------------------------------------------------------------------

LatteParser::Type_Context* LatteParser::DeclContext::type_() {
  return getRuleContext<LatteParser::Type_Context>(0);
}

std::vector<LatteParser::ItemContext *> LatteParser::DeclContext::item() {
  return getRuleContexts<LatteParser::ItemContext>();
}

LatteParser::ItemContext* LatteParser::DeclContext::item(size_t i) {
  return getRuleContext<LatteParser::ItemContext>(i);
}

LatteParser::DeclContext::DeclContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::WhileContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::StmtContext* LatteParser::WhileContext::stmt() {
  return getRuleContext<LatteParser::StmtContext>(0);
}

LatteParser::WhileContext::WhileContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SExpContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::SExpContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::SExpContext::SExpContext(StmtContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::SExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitSExp(this);
  else
    return visitor->visitChildren(this);
}
LatteParser::StmtContext* LatteParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 10, LatteParser::RuleStmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::EmptyContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(96);
      match(LatteParser::T__7);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::BlockStmtContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(97);
      block();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::DeclContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(98);
      type_();
      setState(99);
      item();
      setState(104);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LatteParser::T__6) {
        setState(100);
        match(LatteParser::T__6);
        setState(101);
        item();
        setState(106);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(107);
      match(LatteParser::T__7);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::AssContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(109);
      expr(0);
      setState(110);
      match(LatteParser::T__8);
      setState(111);
      expr(0);
      setState(112);
      match(LatteParser::T__7);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::IncrContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(114);
      expr(0);
      setState(115);
      match(LatteParser::T__9);
      setState(116);
      match(LatteParser::T__7);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::DecrContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(118);
      expr(0);
      setState(119);
      match(LatteParser::T__10);
      setState(120);
      match(LatteParser::T__7);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::RetContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(122);
      match(LatteParser::T__11);
      setState(123);
      expr(0);
      setState(124);
      match(LatteParser::T__7);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::VRetContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(126);
      match(LatteParser::T__11);
      setState(127);
      match(LatteParser::T__7);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::CondContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(128);
      match(LatteParser::T__12);
      setState(129);
      match(LatteParser::T__0);
      setState(130);
      expr(0);
      setState(131);
      match(LatteParser::T__1);
      setState(132);
      stmt();
      break;
    }

    case 10: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::CondElseContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(134);
      match(LatteParser::T__12);
      setState(135);
      match(LatteParser::T__0);
      setState(136);
      expr(0);
      setState(137);
      match(LatteParser::T__1);
      setState(138);
      stmt();
      setState(139);
      match(LatteParser::T__13);
      setState(140);
      stmt();
      break;
    }

    case 11: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::WhileContext>(_localctx));
      enterOuterAlt(_localctx, 11);
      setState(142);
      match(LatteParser::T__14);
      setState(143);
      match(LatteParser::T__0);
      setState(144);
      expr(0);
      setState(145);
      match(LatteParser::T__1);
      setState(146);
      stmt();
      break;
    }

    case 12: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<LatteParser::SExpContext>(_localctx));
      enterOuterAlt(_localctx, 12);
      setState(148);
      expr(0);
      setState(149);
      match(LatteParser::T__7);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_Context ------------------------------------------------------------------

LatteParser::Type_Context::Type_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::Type_Context::getRuleIndex() const {
  return LatteParser::RuleType_;
}

void LatteParser::Type_Context::copyFrom(Type_Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StrContext ------------------------------------------------------------------

LatteParser::StrContext::StrContext(Type_Context *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::StrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitStr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolContext ------------------------------------------------------------------

LatteParser::BoolContext::BoolContext(Type_Context *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::BoolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitBool(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassNameContext ------------------------------------------------------------------

tree::TerminalNode* LatteParser::ClassNameContext::ID() {
  return getToken(LatteParser::ID, 0);
}

LatteParser::ClassNameContext::ClassNameContext(Type_Context *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::ClassNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitClassName(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VoidContext ------------------------------------------------------------------

LatteParser::VoidContext::VoidContext(Type_Context *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::VoidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitVoid(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

LatteParser::IntContext::IntContext(Type_Context *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
LatteParser::Type_Context* LatteParser::type_() {
  Type_Context *_localctx = _tracker.createInstance<Type_Context>(_ctx, getState());
  enterRule(_localctx, 12, LatteParser::RuleType_);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(158);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LatteParser::T__15: {
        _localctx = dynamic_cast<Type_Context *>(_tracker.createInstance<LatteParser::IntContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(153);
        match(LatteParser::T__15);
        break;
      }

      case LatteParser::T__16: {
        _localctx = dynamic_cast<Type_Context *>(_tracker.createInstance<LatteParser::StrContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(154);
        match(LatteParser::T__16);
        break;
      }

      case LatteParser::T__17: {
        _localctx = dynamic_cast<Type_Context *>(_tracker.createInstance<LatteParser::BoolContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(155);
        match(LatteParser::T__17);
        break;
      }

      case LatteParser::T__18: {
        _localctx = dynamic_cast<Type_Context *>(_tracker.createInstance<LatteParser::VoidContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(156);
        match(LatteParser::T__18);
        break;
      }

      case LatteParser::ID: {
        _localctx = dynamic_cast<Type_Context *>(_tracker.createInstance<LatteParser::ClassNameContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(157);
        match(LatteParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ItemContext ------------------------------------------------------------------

LatteParser::ItemContext::ItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LatteParser::ItemContext::ID() {
  return getToken(LatteParser::ID, 0);
}

LatteParser::ExprContext* LatteParser::ItemContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}


size_t LatteParser::ItemContext::getRuleIndex() const {
  return LatteParser::RuleItem;
}

antlrcpp::Any LatteParser::ItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitItem(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::ItemContext* LatteParser::item() {
  ItemContext *_localctx = _tracker.createInstance<ItemContext>(_ctx, getState());
  enterRule(_localctx, 14, LatteParser::RuleItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(164);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(160);
      match(LatteParser::ID);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(161);
      match(LatteParser::ID);
      setState(162);
      match(LatteParser::T__8);
      setState(163);
      expr(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

LatteParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::ExprContext::getRuleIndex() const {
  return LatteParser::RuleExpr;
}

void LatteParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EIdContext ------------------------------------------------------------------

tree::TerminalNode* LatteParser::EIdContext::ID() {
  return getToken(LatteParser::ID, 0);
}

LatteParser::EIdContext::EIdContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EFunCallContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::EFunCallContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::EFunCallContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::EFunCallContext::EFunCallContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EFunCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEFunCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ERelOpContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::ERelOpContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::ERelOpContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::RelOpContext* LatteParser::ERelOpContext::relOp() {
  return getRuleContext<LatteParser::RelOpContext>(0);
}

LatteParser::ERelOpContext::ERelOpContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::ERelOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitERelOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ETrueContext ------------------------------------------------------------------

LatteParser::ETrueContext::ETrueContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::ETrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitETrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EOrContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::EOrContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::EOrContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::EOrContext::EOrContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EIntContext ------------------------------------------------------------------

tree::TerminalNode* LatteParser::EIntContext::INT() {
  return getToken(LatteParser::INT, 0);
}

LatteParser::EIntContext::EIntContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EMemberExprContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::EMemberExprContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::EMemberExprContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::EMemberExprContext::EMemberExprContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EMemberExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEMemberExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EUnOpContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::EUnOpContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::EUnOpContext::EUnOpContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EUnOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEUnOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EStrContext ------------------------------------------------------------------

tree::TerminalNode* LatteParser::EStrContext::STR() {
  return getToken(LatteParser::STR, 0);
}

LatteParser::EStrContext::EStrContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EStrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEStr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EMulOpContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::EMulOpContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::EMulOpContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::MulOpContext* LatteParser::EMulOpContext::mulOp() {
  return getRuleContext<LatteParser::MulOpContext>(0);
}

LatteParser::EMulOpContext::EMulOpContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EMulOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEMulOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EAndContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::EAndContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::EAndContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::EAndContext::EAndContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EParenContext ------------------------------------------------------------------

LatteParser::ExprContext* LatteParser::EParenContext::expr() {
  return getRuleContext<LatteParser::ExprContext>(0);
}

LatteParser::EParenContext::EParenContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EFalseContext ------------------------------------------------------------------

LatteParser::EFalseContext::EFalseContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EFalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEFalse(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EAddOpContext ------------------------------------------------------------------

std::vector<LatteParser::ExprContext *> LatteParser::EAddOpContext::expr() {
  return getRuleContexts<LatteParser::ExprContext>();
}

LatteParser::ExprContext* LatteParser::EAddOpContext::expr(size_t i) {
  return getRuleContext<LatteParser::ExprContext>(i);
}

LatteParser::AddOpContext* LatteParser::EAddOpContext::addOp() {
  return getRuleContext<LatteParser::AddOpContext>(0);
}

LatteParser::EAddOpContext::EAddOpContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any LatteParser::EAddOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitEAddOp(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::ExprContext* LatteParser::expr() {
   return expr(0);
}

LatteParser::ExprContext* LatteParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LatteParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  LatteParser::ExprContext *previousContext = _localctx;
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, LatteParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(178);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LatteParser::T__19:
      case LatteParser::T__20: {
        _localctx = _tracker.createInstance<EUnOpContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(167);
        _la = _input->LA(1);
        if (!(_la == LatteParser::T__19

        || _la == LatteParser::T__20)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(168);
        expr(13);
        break;
      }

      case LatteParser::ID: {
        _localctx = _tracker.createInstance<EIdContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(169);
        match(LatteParser::ID);
        break;
      }

      case LatteParser::INT: {
        _localctx = _tracker.createInstance<EIntContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(170);
        match(LatteParser::INT);
        break;
      }

      case LatteParser::T__24: {
        _localctx = _tracker.createInstance<ETrueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(171);
        match(LatteParser::T__24);
        break;
      }

      case LatteParser::T__25: {
        _localctx = _tracker.createInstance<EFalseContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(172);
        match(LatteParser::T__25);
        break;
      }

      case LatteParser::STR: {
        _localctx = _tracker.createInstance<EStrContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(173);
        match(LatteParser::STR);
        break;
      }

      case LatteParser::T__0: {
        _localctx = _tracker.createInstance<EParenContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(174);
        match(LatteParser::T__0);
        setState(175);
        expr(0);
        setState(176);
        match(LatteParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(216);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(214);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<EMulOpContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(180);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(181);
          mulOp();
          setState(182);
          expr(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<EAddOpContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(184);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(185);
          addOp();
          setState(186);
          expr(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ERelOpContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(188);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(189);
          relOp();
          setState(190);
          expr(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<EAndContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(192);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(193);
          match(LatteParser::T__21);
          setState(194);
          expr(9);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<EOrContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(195);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(196);
          match(LatteParser::T__22);
          setState(197);
          expr(8);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<EMemberExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(198);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(199);
          match(LatteParser::T__23);
          setState(200);
          expr(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<EFunCallContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(201);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(202);
          match(LatteParser::T__0);
          setState(211);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << LatteParser::T__0)
            | (1ULL << LatteParser::T__19)
            | (1ULL << LatteParser::T__20)
            | (1ULL << LatteParser::T__24)
            | (1ULL << LatteParser::T__25)
            | (1ULL << LatteParser::INT)
            | (1ULL << LatteParser::ID)
            | (1ULL << LatteParser::STR))) != 0)) {
            setState(203);
            expr(0);
            setState(208);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == LatteParser::T__6) {
              setState(204);
              match(LatteParser::T__6);
              setState(205);
              expr(0);
              setState(210);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
          }
          setState(213);
          match(LatteParser::T__1);
          break;
        }

        } 
      }
      setState(218);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddOpContext ------------------------------------------------------------------

LatteParser::AddOpContext::AddOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::AddOpContext::getRuleIndex() const {
  return LatteParser::RuleAddOp;
}

antlrcpp::Any LatteParser::AddOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitAddOp(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::AddOpContext* LatteParser::addOp() {
  AddOpContext *_localctx = _tracker.createInstance<AddOpContext>(_ctx, getState());
  enterRule(_localctx, 18, LatteParser::RuleAddOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    _la = _input->LA(1);
    if (!(_la == LatteParser::T__19

    || _la == LatteParser::T__26)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulOpContext ------------------------------------------------------------------

LatteParser::MulOpContext::MulOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::MulOpContext::getRuleIndex() const {
  return LatteParser::RuleMulOp;
}

antlrcpp::Any LatteParser::MulOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitMulOp(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::MulOpContext* LatteParser::mulOp() {
  MulOpContext *_localctx = _tracker.createInstance<MulOpContext>(_ctx, getState());
  enterRule(_localctx, 20, LatteParser::RuleMulOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LatteParser::T__27)
      | (1ULL << LatteParser::T__28)
      | (1ULL << LatteParser::T__29))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelOpContext ------------------------------------------------------------------

LatteParser::RelOpContext::RelOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LatteParser::RelOpContext::getRuleIndex() const {
  return LatteParser::RuleRelOp;
}

antlrcpp::Any LatteParser::RelOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LatteVisitor*>(visitor))
    return parserVisitor->visitRelOp(this);
  else
    return visitor->visitChildren(this);
}

LatteParser::RelOpContext* LatteParser::relOp() {
  RelOpContext *_localctx = _tracker.createInstance<RelOpContext>(_ctx, getState());
  enterRule(_localctx, 22, LatteParser::RuleRelOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LatteParser::T__30)
      | (1ULL << LatteParser::T__31)
      | (1ULL << LatteParser::T__32)
      | (1ULL << LatteParser::T__33)
      | (1ULL << LatteParser::T__34)
      | (1ULL << LatteParser::T__35))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool LatteParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 8: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LatteParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 12);
    case 1: return precpred(_ctx, 11);
    case 2: return precpred(_ctx, 10);
    case 3: return precpred(_ctx, 9);
    case 4: return precpred(_ctx, 8);
    case 5: return precpred(_ctx, 7);
    case 6: return precpred(_ctx, 14);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> LatteParser::_decisionToDFA;
atn::PredictionContextCache LatteParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN LatteParser::_atn;
std::vector<uint16_t> LatteParser::_serializedATN;

std::vector<std::string> LatteParser::_ruleNames = {
  "program", "topDef", "classItem", "arg", "block", "stmt", "type_", "item", 
  "expr", "addOp", "mulOp", "relOp"
};

std::vector<std::string> LatteParser::_literalNames = {
  "", "'('", "')'", "'class'", "':'", "'{'", "'}'", "','", "';'", "'='", 
  "'++'", "'--'", "'return'", "'if'", "'else'", "'while'", "'int'", "'string'", 
  "'boolean'", "'void'", "'-'", "'!'", "'&&'", "'||'", "'.'", "'true'", 
  "'false'", "'+'", "'*'", "'/'", "'%'", "'<'", "'<='", "'>'", "'>='", "'=='", 
  "'!='"
};

std::vector<std::string> LatteParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "COMMENT", "MULTICOMMENT", "INT", "ID", "WS", "STR"
};

dfa::Vocabulary LatteParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> LatteParser::_tokenNames;

LatteParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x2c, 0xe4, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x6, 0x2, 0x1c, 
    0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x1d, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x24, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x2d, 0xa, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x7, 0x3, 0x31, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x34, 0xb, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x37, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x7, 0x4, 0x3d, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x40, 0xb, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x48, 0xa, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x4d, 0xa, 0x4, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x55, 0xa, 
    0x5, 0xc, 0x5, 0xe, 0x5, 0x58, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 
    0x5c, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x5f, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 
    0x69, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x6c, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x5, 0x7, 0x9a, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x5, 0x8, 0xa1, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x5, 0x9, 0xa7, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0xb5, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x7, 0xa, 0xd1, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xd4, 0xb, 0xa, 
    0x5, 0xa, 0xd6, 0xa, 0xa, 0x3, 0xa, 0x7, 0xa, 0xd9, 0xa, 0xa, 0xc, 0xa, 
    0xe, 0xa, 0xdc, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x2, 0x3, 0x12, 0xe, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x2, 0x6, 0x3, 0x2, 0x16, 0x17, 
    0x4, 0x2, 0x16, 0x16, 0x1d, 0x1d, 0x3, 0x2, 0x1e, 0x20, 0x3, 0x2, 0x21, 
    0x26, 0x2, 0x101, 0x2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x4, 0x36, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4e, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x59, 0x3, 0x2, 0x2, 0x2, 0xc, 0x99, 0x3, 0x2, 0x2, 0x2, 0xe, 0xa0, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0xa6, 0x3, 0x2, 0x2, 0x2, 0x12, 0xb4, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x16, 0xdf, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0xe1, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1c, 0x5, 0x4, 0x3, 
    0x2, 0x1b, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x5, 0xe, 0x8, 0x2, 0x20, 0x21, 
    0x7, 0x2a, 0x2, 0x2, 0x21, 0x23, 0x7, 0x3, 0x2, 0x2, 0x22, 0x24, 0x5, 
    0x8, 0x5, 0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x7, 0x4, 0x2, 
    0x2, 0x26, 0x27, 0x5, 0xa, 0x6, 0x2, 0x27, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x28, 0x29, 0x7, 0x5, 0x2, 0x2, 0x29, 0x2c, 0x7, 0x2a, 0x2, 0x2, 0x2a, 
    0x2b, 0x7, 0x6, 0x2, 0x2, 0x2b, 0x2d, 0x7, 0x2a, 0x2, 0x2, 0x2c, 0x2a, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x32, 0x7, 0x7, 0x2, 0x2, 0x2f, 0x31, 0x5, 0x6, 
    0x4, 0x2, 0x30, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x34, 0x3, 0x2, 0x2, 
    0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 0x2, 
    0x33, 0x35, 0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x37, 0x7, 0x8, 0x2, 0x2, 0x36, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x36, 0x28, 
    0x3, 0x2, 0x2, 0x2, 0x37, 0x5, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x5, 
    0xe, 0x8, 0x2, 0x39, 0x3e, 0x5, 0x10, 0x9, 0x2, 0x3a, 0x3b, 0x7, 0x9, 
    0x2, 0x2, 0x3b, 0x3d, 0x5, 0x10, 0x9, 0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 
    0x2, 0x3d, 0x40, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 
    0x3e, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x41, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x3e, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x7, 0xa, 0x2, 0x2, 0x42, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x5, 0xe, 0x8, 0x2, 0x44, 0x45, 0x7, 
    0x2a, 0x2, 0x2, 0x45, 0x47, 0x7, 0x3, 0x2, 0x2, 0x46, 0x48, 0x5, 0x8, 
    0x5, 0x2, 0x47, 0x46, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x7, 0x4, 0x2, 0x2, 
    0x4a, 0x4b, 0x5, 0xa, 0x6, 0x2, 0x4b, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4c, 
    0x38, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x43, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x5, 0xe, 0x8, 0x2, 0x4f, 0x56, 0x7, 
    0x2a, 0x2, 0x2, 0x50, 0x51, 0x7, 0x9, 0x2, 0x2, 0x51, 0x52, 0x5, 0xe, 
    0x8, 0x2, 0x52, 0x53, 0x7, 0x2a, 0x2, 0x2, 0x53, 0x55, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x50, 0x3, 0x2, 0x2, 0x2, 0x55, 0x58, 0x3, 0x2, 0x2, 0x2, 
    0x56, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x58, 0x56, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5d, 
    0x7, 0x7, 0x2, 0x2, 0x5a, 0x5c, 0x5, 0xc, 0x7, 0x2, 0x5b, 0x5a, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 
    0x2, 0x2, 0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x60, 0x3, 0x2, 0x2, 
    0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x7, 0x8, 0x2, 0x2, 
    0x61, 0xb, 0x3, 0x2, 0x2, 0x2, 0x62, 0x9a, 0x7, 0xa, 0x2, 0x2, 0x63, 
    0x9a, 0x5, 0xa, 0x6, 0x2, 0x64, 0x65, 0x5, 0xe, 0x8, 0x2, 0x65, 0x6a, 
    0x5, 0x10, 0x9, 0x2, 0x66, 0x67, 0x7, 0x9, 0x2, 0x2, 0x67, 0x69, 0x5, 
    0x10, 0x9, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6c, 0x3, 0x2, 
    0x2, 0x2, 0x6a, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 
    0x6d, 0x6e, 0x7, 0xa, 0x2, 0x2, 0x6e, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0x70, 0x5, 0x12, 0xa, 0x2, 0x70, 0x71, 0x7, 0xb, 0x2, 0x2, 0x71, 0x72, 
    0x5, 0x12, 0xa, 0x2, 0x72, 0x73, 0x7, 0xa, 0x2, 0x2, 0x73, 0x9a, 0x3, 
    0x2, 0x2, 0x2, 0x74, 0x75, 0x5, 0x12, 0xa, 0x2, 0x75, 0x76, 0x7, 0xc, 
    0x2, 0x2, 0x76, 0x77, 0x7, 0xa, 0x2, 0x2, 0x77, 0x9a, 0x3, 0x2, 0x2, 
    0x2, 0x78, 0x79, 0x5, 0x12, 0xa, 0x2, 0x79, 0x7a, 0x7, 0xd, 0x2, 0x2, 
    0x7a, 0x7b, 0x7, 0xa, 0x2, 0x2, 0x7b, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x7c, 
    0x7d, 0x7, 0xe, 0x2, 0x2, 0x7d, 0x7e, 0x5, 0x12, 0xa, 0x2, 0x7e, 0x7f, 
    0x7, 0xa, 0x2, 0x2, 0x7f, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x80, 0x81, 0x7, 
    0xe, 0x2, 0x2, 0x81, 0x9a, 0x7, 0xa, 0x2, 0x2, 0x82, 0x83, 0x7, 0xf, 
    0x2, 0x2, 0x83, 0x84, 0x7, 0x3, 0x2, 0x2, 0x84, 0x85, 0x5, 0x12, 0xa, 
    0x2, 0x85, 0x86, 0x7, 0x4, 0x2, 0x2, 0x86, 0x87, 0x5, 0xc, 0x7, 0x2, 
    0x87, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x7, 0xf, 0x2, 0x2, 0x89, 
    0x8a, 0x7, 0x3, 0x2, 0x2, 0x8a, 0x8b, 0x5, 0x12, 0xa, 0x2, 0x8b, 0x8c, 
    0x7, 0x4, 0x2, 0x2, 0x8c, 0x8d, 0x5, 0xc, 0x7, 0x2, 0x8d, 0x8e, 0x7, 
    0x10, 0x2, 0x2, 0x8e, 0x8f, 0x5, 0xc, 0x7, 0x2, 0x8f, 0x9a, 0x3, 0x2, 
    0x2, 0x2, 0x90, 0x91, 0x7, 0x11, 0x2, 0x2, 0x91, 0x92, 0x7, 0x3, 0x2, 
    0x2, 0x92, 0x93, 0x5, 0x12, 0xa, 0x2, 0x93, 0x94, 0x7, 0x4, 0x2, 0x2, 
    0x94, 0x95, 0x5, 0xc, 0x7, 0x2, 0x95, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x96, 
    0x97, 0x5, 0x12, 0xa, 0x2, 0x97, 0x98, 0x7, 0xa, 0x2, 0x2, 0x98, 0x9a, 
    0x3, 0x2, 0x2, 0x2, 0x99, 0x62, 0x3, 0x2, 0x2, 0x2, 0x99, 0x63, 0x3, 
    0x2, 0x2, 0x2, 0x99, 0x64, 0x3, 0x2, 0x2, 0x2, 0x99, 0x6f, 0x3, 0x2, 
    0x2, 0x2, 0x99, 0x74, 0x3, 0x2, 0x2, 0x2, 0x99, 0x78, 0x3, 0x2, 0x2, 
    0x2, 0x99, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x99, 0x80, 0x3, 0x2, 0x2, 0x2, 
    0x99, 0x82, 0x3, 0x2, 0x2, 0x2, 0x99, 0x88, 0x3, 0x2, 0x2, 0x2, 0x99, 
    0x90, 0x3, 0x2, 0x2, 0x2, 0x99, 0x96, 0x3, 0x2, 0x2, 0x2, 0x9a, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x9b, 0xa1, 0x7, 0x12, 0x2, 0x2, 0x9c, 0xa1, 0x7, 
    0x13, 0x2, 0x2, 0x9d, 0xa1, 0x7, 0x14, 0x2, 0x2, 0x9e, 0xa1, 0x7, 0x15, 
    0x2, 0x2, 0x9f, 0xa1, 0x7, 0x2a, 0x2, 0x2, 0xa0, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0xa0, 0x9c, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9d, 0x3, 0x2, 0x2, 0x2, 
    0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa1, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa7, 0x7, 0x2a, 0x2, 0x2, 0xa3, 0xa4, 
    0x7, 0x2a, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0xb, 0x2, 0x2, 0xa5, 0xa7, 0x5, 
    0x12, 0xa, 0x2, 0xa6, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa3, 0x3, 0x2, 
    0x2, 0x2, 0xa7, 0x11, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x8, 0xa, 0x1, 
    0x2, 0xa9, 0xaa, 0x9, 0x2, 0x2, 0x2, 0xaa, 0xb5, 0x5, 0x12, 0xa, 0xf, 
    0xab, 0xb5, 0x7, 0x2a, 0x2, 0x2, 0xac, 0xb5, 0x7, 0x29, 0x2, 0x2, 0xad, 
    0xb5, 0x7, 0x1b, 0x2, 0x2, 0xae, 0xb5, 0x7, 0x1c, 0x2, 0x2, 0xaf, 0xb5, 
    0x7, 0x2c, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x3, 0x2, 0x2, 0xb1, 0xb2, 0x5, 
    0x12, 0xa, 0x2, 0xb2, 0xb3, 0x7, 0x4, 0x2, 0x2, 0xb3, 0xb5, 0x3, 0x2, 
    0x2, 0x2, 0xb4, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xab, 0x3, 0x2, 0x2, 
    0x2, 0xb4, 0xac, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0xb4, 0xae, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb4, 
    0xb0, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xda, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 
    0xc, 0xe, 0x2, 0x2, 0xb7, 0xb8, 0x5, 0x16, 0xc, 0x2, 0xb8, 0xb9, 0x5, 
    0x12, 0xa, 0xf, 0xb9, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0xc, 0xd, 
    0x2, 0x2, 0xbb, 0xbc, 0x5, 0x14, 0xb, 0x2, 0xbc, 0xbd, 0x5, 0x12, 0xa, 
    0xe, 0xbd, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0xc, 0xc, 0x2, 0x2, 
    0xbf, 0xc0, 0x5, 0x18, 0xd, 0x2, 0xc0, 0xc1, 0x5, 0x12, 0xa, 0xd, 0xc1, 
    0xd9, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0xc, 0xb, 0x2, 0x2, 0xc3, 0xc4, 
    0x7, 0x18, 0x2, 0x2, 0xc4, 0xd9, 0x5, 0x12, 0xa, 0xb, 0xc5, 0xc6, 0xc, 
    0xa, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x19, 0x2, 0x2, 0xc7, 0xd9, 0x5, 0x12, 
    0xa, 0xa, 0xc8, 0xc9, 0xc, 0x9, 0x2, 0x2, 0xc9, 0xca, 0x7, 0x1a, 0x2, 
    0x2, 0xca, 0xd9, 0x5, 0x12, 0xa, 0xa, 0xcb, 0xcc, 0xc, 0x10, 0x2, 0x2, 
    0xcc, 0xd5, 0x7, 0x3, 0x2, 0x2, 0xcd, 0xd2, 0x5, 0x12, 0xa, 0x2, 0xce, 
    0xcf, 0x7, 0x9, 0x2, 0x2, 0xcf, 0xd1, 0x5, 0x12, 0xa, 0x2, 0xd0, 0xce, 
    0x3, 0x2, 0x2, 0x2, 0xd1, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd0, 0x3, 
    0x2, 0x2, 0x2, 0xd2, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd6, 0x3, 0x2, 
    0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xcd, 0x3, 0x2, 0x2, 
    0x2, 0xd5, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd7, 0x3, 0x2, 0x2, 0x2, 
    0xd7, 0xd9, 0x7, 0x4, 0x2, 0x2, 0xd8, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xd8, 
    0xba, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xc2, 
    0x3, 0x2, 0x2, 0x2, 0xd8, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xc8, 0x3, 
    0x2, 0x2, 0x2, 0xd8, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xdc, 0x3, 0x2, 
    0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 
    0x2, 0xdb, 0x13, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xda, 0x3, 0x2, 0x2, 0x2, 
    0xdd, 0xde, 0x9, 0x3, 0x2, 0x2, 0xde, 0x15, 0x3, 0x2, 0x2, 0x2, 0xdf, 
    0xe0, 0x9, 0x4, 0x2, 0x2, 0xe0, 0x17, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 
    0x9, 0x5, 0x2, 0x2, 0xe2, 0x19, 0x3, 0x2, 0x2, 0x2, 0x15, 0x1d, 0x23, 
    0x2c, 0x32, 0x36, 0x3e, 0x47, 0x4c, 0x56, 0x5d, 0x6a, 0x99, 0xa0, 0xa6, 
    0xb4, 0xd2, 0xd5, 0xd8, 0xda, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

LatteParser::Initializer LatteParser::_init;
