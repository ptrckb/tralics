#pragma once
// -*- C++ -*-
// TRALICS, copyright (C)INRIA/apics (Jose' Grimm) 2003,2007,2008

// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use,
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
// (See the file COPYING in the main directory for details)

// This file contains some inline functions and the tralics
// namespace declarations

// We also declare some global variables here

#include "tralics/MainClass.h"
#include "txlogger.h"
#include "txparam.h"

// See comments in tralics.cpp where these variables are defined
namespace main_ns {
    extern HalfLogger log_or_tty;
    extern Buffer     path_buffer;
    extern int        nb_errs;
    extern bool       file_ended;
    extern bool       no_xml_error;
    extern bool       use_quotes;
    extern bool       bib_allow_break;
} // namespace main_ns

namespace tralics_ns {
    auto exists(const std::vector<std::string> &ST, const std::string &d) -> bool;
    auto file_exists(const std::string &name) -> bool;
    auto find_in_confdir(const std::string &s, bool retry) -> bool; ///< Try to open the file, using alt location if needed
    auto find_in_path(const std::string &s) -> bool;                ///< Tries to open a TeX file
    auto get_out_dir(const std::string &name) -> String;            /// Returns output_dir+name
    auto get_short_jobname() -> std::string;
    auto is_leap_year(long y) -> bool;
    auto only_digits(const std::string &s) -> bool;
    auto open_file(const std::string &name, bool f) -> std::ofstream;
    auto open_file(String name, bool fatal) -> std::ofstream;
    auto titlepage_is_valid() -> bool;

    void bibtex_boot(String b, String dy, std::string no_year, bool inra, bool db);
    void bibtex_insert_jobname();
    void bibtex_set_nocite();
    void boot_math(bool mv);
    void read_a_file(LinePtr &L, const std::string &x, int spec);
    void Titlepage_create(LinePtr &lines);
    void Titlepage_start(bool verbose);
} // namespace tralics_ns

namespace err_ns {
    extern Buffer local_buf;
    void          fatal_error(String s);
} // namespace err_ns

namespace config_ns {
    auto find_one_key(const std::string &name, const std::string &key) -> std::string;
    auto pers_rc(const std::string &rc) -> std::string;
    void check_RC(Buffer &B, Xml *res);
    auto find_keys(const std::string &name) -> std::string;
    auto start_interpret(Buffer &B, String s) -> bool;
    void interpret_list(const std::string &a, Buffer &B);
    auto assign_name(String A, String B) -> bool;
    auto assign_att(String A, String B) -> bool;
} // namespace config_ns

inline auto operator==(const Buffer &B, String s) -> bool { return strcmp(B.c_str(), s) == 0; }

inline auto is_vowel(char c) -> bool { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }

// True if it is an accent character, like \^.
inline auto is_accent_char(char c) -> bool { return c == '\'' || c == '`' || c == '^' || c == '"' || c == '~' || c == '.' || c == '='; }

inline auto is_tp_delim(char c) -> bool { return c == '<' || c == '\\' || c == '"'; }

inline auto operator==(Token a, Token b) -> bool { return a.val == b.val; }

inline auto operator!=(Token a, Token b) -> bool { return a.val != b.val; }

inline Istring::Istring(const Buffer &X) : id(SH.find(X.c_str())) {}

inline Istring::Istring(String s) : id(SH.find(s)) {}

inline Istring::Istring(const std::string &s) : id(SH.find(s)) {}

inline auto Istring::c_str() const -> String { return SH[id]; }

inline auto Istring::p_str() const -> std::string { return SH.p_str(id); }
