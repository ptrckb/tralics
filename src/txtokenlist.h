#pragma once
// -*- C++ -*-
// Copyright INRIA/apics (Jose' Grimm)  2006, 2007,2008

// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use,
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
// (See the file COPYING in the main directory for details)

#include "tralics/FpNum.h"
#include "tralics/Token.h"
#include <string>
#include <utility>

class Hashtab;

namespace token_ns {
    auto fast_get_block(TokenList &L) -> TokenList;
    void fast_get_block(TokenList &L, TokenList &res);
    auto get_a_param(TokenList &L, bool br) -> TokenList;
    auto get_block(TokenList &L) -> TokenList;
    auto get_unique(TokenList &L) -> Token;
    void get_unique(TokenList &L, Token &t1, Token &t2);
    auto has_a_single_token(const TokenList &L) -> bool;
    auto has_a_single_token(const TokenList &L, Token t) -> bool;
    auto posint_to_list(long n) -> TokenList;
    void push_back_i(TokenList &L, long n);
    void remove_block(TokenList &L);
    void remove_ext_braces(TokenList &L);
    void remove_initial_spaces(TokenList &L);
    void remove_first_last_space(TokenList &L);
    void replace(TokenList &A, Token x1, Token x2);
    auto replace_space(TokenList &A, Token x2, Token x3) -> int;
    void show(const TokenList &);
    auto split_at(Token e, Token m, Token m1, TokenList &L, TokenList &z, bool s) -> bool;
    auto string_to_list(const std::string &s, bool b) -> TokenList;
    void double_hack(TokenList &key);
    auto split_at(Token m, TokenList &L, TokenList &z) -> bool;
    auto is_sublist(TokenList::iterator A, TokenList::iterator B, int n) -> bool;
    auto is_in(TokenList &A, TokenList &B, bool remove, int &is_in_skipped) -> bool;
    void normalise_list(char c, TokenList &L);
    void sanitize_one(TokenList &L, uchar c);
    void sanitize_one(TokenList &L, TokenList &s, long n);
    void sanitize_one(TokenList &L);
    auto check_brace(Token x, int &bl) -> bool;
    auto compare(const TokenList &A, const TokenList &B) -> bool;
} // namespace token_ns

// This is for fp
class FpGenList {
public:
    TokenList value;

    FpGenList(TokenList A) : value(std::move(A)) {}
    void add_last_space(String S);
    void add_last_space(TokenList &W, String S);
    auto find_str(int &n) const -> Token;
    void fp_gen_add();
    void fp_gen_app();
    void fp_gen_exp();
    void fp_gen_komma();
    void fp_gen_mul();
    void push_back(Token L) { value.push_back(L); }
    void push_back(TokenList &L) { value.splice(value.end(), L); }
    void remove_first_n(int n);
    void remove_spaces();
    void split_after(int n, TokenList &z);
    auto split_at(Token x, Token x2, TokenList &z) -> Token;
    void split_after(TokenList::iterator X, TokenList &z);
    auto split_at_p(TokenList &A, TokenList &B) -> bool;
    void to_postfix();
    void fp_check_paren();
};

//
class FpStack {
    TokenList value;

public:
    void               clear() { value.clear(); }
    [[nodiscard]] auto empty() const -> bool { return value.empty(); }
    void               pop_upn(FpNum &x);
    void               pop_upn(TokenList &L);
    void               push_front(Token L) { value.push_front(L); }
    void               push_front(TokenList &L) { value.splice(value.begin(), L); }
    void               push_upn(TokenList &L);
    void               push_upn(FpNum x);
};

// This represents the value of a user-defined command
class Macro {
    std::array<TokenList, 10> delimiters; // delimiters between arguments
public:
    size_t    nbargs{0};       // number of arguments
    def_type  type{dt_normal}; // type of macro
    TokenList body;            // the body

    Macro() = default;
    Macro(TokenList L) : body(std::move(L)) { correct_type(); }

    void               set_nbargs(size_t n) { nbargs = n; } // \todo remove
    void               set_type(def_type n) { type = n; }
    [[nodiscard]] auto is_same(const Macro &aux) const -> bool;
    auto               operator[](size_t n) const -> const TokenList & { return delimiters[n]; }
    void               set_delimiters(size_t k, TokenList L) { delimiters[k] = std::move(L); }
    void               correct_type();
};

auto operator<<(std::ostream &fp, const Macro &x) -> std::ostream &;
