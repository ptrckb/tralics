#pragma once
// -*- C++ -*-
// TRALICS, copyright (C) INRIA/apics (Jose' Grimm) 2002, 2007,2008

// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use,
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
// (See the file COPYING in the main directory for details)

#include "tralics/CitationKey.h"
#include "tralics/Xml.h"
#include "txinline.h"

class CitationItem {
    Istring key;
    Istring from;
    Istring bid;
    Xid     solved;

public:
    auto               get_bid() -> Istring;
    void               set_id(Istring x) { bid = std::move(x); }
    auto               has_empty_id() -> bool { return bid.empty(); }
    void               set_solved(Xid N) { solved = N; }
    void               dump(Buffer &b) const;
    void               dump_bibtex();
    auto               match(const Istring &A, const Istring &B) -> bool;
    auto               match_star(const Istring &A) -> bool;
    [[nodiscard]] auto is_solved() const -> bool { return solved.value != 0; }
    CitationItem(Istring A, Istring B) : key(std::move(A)), from(std::move(B)), bid("") {}
};

class Bibliography {
public:
    std::string               bib_style{"plain"}; // The bibliography style
    std::string               cmd;                // The bibliography command
    std::vector<CitationItem> citation_table;
    Xml *                     location{nullptr}; // location of biblio in the XML tree

private:
    std::vector<std::string> biblio_src;              // database file names
    bool                     nocite{false};           // have  we seen \nocite* ?
    bool                     biblio_loc_force{false}; // force location
    int                      last_bid{-1};            // current number for unique_bid

public:
    void               dump(Buffer &b);
    void               dump_bibtex();
    void               dump_data(Buffer &b);
    auto               get_bid(size_t n) { return citation_table[n].get_bid(); }
    auto               find_citation_item(const Istring &from, const Istring &key, bool insert) -> std::optional<size_t>;
    auto               find_citation_star(const Istring &from, const Istring &key) -> size_t;
    [[nodiscard]] auto has_cmd() const -> bool { return !cmd.empty(); }
    [[nodiscard]] auto location_exists() const -> bool { return biblio_loc_force; }
    auto               number_of_data_bases() { return biblio_src.size(); }
    void               push_back_src(const std::string &x) { biblio_src.emplace_back(x); }
    [[nodiscard]] auto seen_nocite() const -> bool { return nocite; }
    void               set_cmd(std::string x) { cmd = std::move(x); }
    void               set_location(Xml *X, bool f) {
        location         = X;
        biblio_loc_force = f;
    }
    void set_nocite() { nocite = true; }
    void set_style(std::string x) { bib_style = std::move(x); }
    void stats();
    auto unique_bid() -> Istring;
};

// A bibtex macro, like @string(foo="bar")
class BibMacro {
private:
    size_t      h{};  // hash code of the name
    std::string name; // the name of the name (e.g. foo)
public:
    std::string value; // the value of the macro (e.g. bar)

    auto is_same(size_t hash, const std::string &s) -> bool { return hash == h && name == s; } // \todo operator==
    void set_value(std::string v) { value = std::move(v); }
    void set_default_value() { value = name; }
    BibMacro() = default;
    BibMacro(size_t hash, Buffer &s1) : h(hash), name(s1) {}
    BibMacro(size_t hash, String &s1, String s2) : h(hash), name(s1), value(s2) {}
};

// Consider for instance the name list :
// Carrasco, J. and MahEEvas, S. and Rubino, G. and Su\~nEE, V.
// (where EE stands for \'e on 8 bits)
// value will be \bpers{}\bpers{}\bpers{}\bpers (concatenation of 4 value)
// long_key will be the concatenation of 4?
// short_key will be CMRS
class BibtexName {
public:
    std::string value;
    std::string long_key;
    std::string short_key;
    std::string name_key;
};

// A bibliographic entry \todo derive from CitationKey?
class BibEntry {
    friend class Bibtex;

    BibEntry *                          crossref{nullptr};      // In case of a crossref
    BibEntry *                          crossref_from{nullptr}; // reverse crossref
    entry_type                          type_int{type_unknown}; // the type of the entry
    CitationKey                         cite_key;               // the cite_key structure
    bib_creator                         why_me{};               // reason why this entry is considered
    std::array<std::string, fp_unknown> all_fields;             // all the fields
    BibtexName                          author_data;            // already processed author data
    BibtexName                          editor_data;            // already processed editor data

    int                      extra_num{0};     // extra char added to the label
    int                      cur_year{0};      // current year, if year field can be parsed
    std::string              lab1, lab2, lab3; // two temporaries.
    size_t                   id{0};
    bool                     explicit_cit{false};
    c_primaire               main_c_type{};
    c_secondaire             second_c_type{};
    int                      first_line{-1};
    std::vector<std::string> user_fields;
    size_t                   is_extension{};

public:
    std::string label, sort_label, aux_label; // cite label and sort label
    Istring     unique_id{""};

    BibEntry();

private:
    [[nodiscard]] auto from_to_string() const -> std::string { return cite_key.from_to_string(); };
    [[nodiscard]] auto ra_prefix() const -> String;
    [[nodiscard]] auto get_cite_prefix() const -> bib_from { return cite_key.cite_prefix; }

    void find_cnrs_type(Buffer &);
    void output_bibitem();
    void out_something(field_pos p);
    void out_something(field_pos p, size_t w);
    void set_explicit_cit() { explicit_cit = true; }
    auto is_empty(String s) -> bool;
    void move_to_year() { cite_key.move_to_year(); }
    void use_extra_num();
    void numeric_label(long i);
    void call_type();
    void call_type_all();
    void call_type_special();
    void format_series_etc(bool pa);
    void sort_author(bool au);
    void sort_editor();
    void sort_organization();
    void sort_check(String);
    void presort(long serial);
    void sort_key();
    void format_author(bool au);
    void forward_pass(std::string &previous_label, int &last_num);
    void reverse_pass(int &next_extra);
    auto find_all_names(String) -> BibtexName *;
    auto format_lab_names(String s) -> String;
    auto sort_format_names(String s) -> String;
    void normalise();
    void un_crossref();
    void copy_from(BibEntry *Y);
    void copy_from(BibEntry *Y, size_t k);
    void normalise_statut(Buffer &);
    void one_cnrs_aux(Buffer &A, bool &nf, field_pos p, String aux);
    void add_warning(int dy);
    auto store_field(field_pos where) -> bool;
    void parse_crossref();
    void work(long serial);

    static void handle_one_namelist(std::string &s, BibtexName &X);
    static void out_something(field_pos p, const std::string &s);
};

class Berror {};

class Bibtex {
private:
    Buffer                   inbuf;             // contains a line of the bib file
    std::vector<codepoint>   input_line;        // line as Utf8Chars
    size_t                   input_line_pos{0}; // position in input_line
    Buffer                   token_buf;
    LinePtr                  in_lines;       // contains the bibfile
    String                   src_name{};     // name of the bibfile
    int                      cur_bib_line{}; // current line number
    int                      last_ok_line{}; // start of current entry
    char                     right_outer_delim{};
    std::vector<BibMacro>    all_macros;
    std::vector<BibEntry *>  all_entries;       // potential entries
    std::vector<BibEntry *>  all_entries_table; // real entries
    std::vector<std::string> user_model;
    bib_from                 entry_prefix{};
    bool                     nocitestar{false};
    bool                     normal_biblio{true};
    bool                     refer_biblio{};
    bool                     in_ra{};
    std::string              default_year;
    bool                     want_numeric{};
    std::string              cur_field_name;
    std::string              no_year;
    bool                     noyearerror{};
    bool                     interactive{false};
    std::array<id_type, 128> id_class{};

public:
    Bibtex(std::string dy) : default_year(std::move(dy)) {}

    auto               find_entry(const CitationKey &s) -> BibEntry *;
    auto               find_entry(const std::string &s, const std::string &prefix, bib_creator bc) -> BibEntry *;
    auto               find_entry(const std::string &s, bool create, bib_creator bc) -> BibEntry *;
    auto               make_new_entry(const CitationKey &a, bib_creator b) -> BibEntry *;
    void               make_entry(const CitationKey &a, Istring myid);
    [[nodiscard]] auto auto_cite() const -> bool;
    [[nodiscard]] auto default_prefix() const -> bib_from { return entry_prefix; }

private:
    [[nodiscard]] auto at_eol() const -> bool { return input_line_pos >= input_line.size(); }
    void               advance() { input_line_pos++; }
    auto               check_val_end() -> int;
    auto               check_entry_end() -> int;
    auto               check_entry_end(int k) -> int;
    auto               check_field_end(size_t what) -> int;
    auto               cur_char() -> codepoint { return input_line[input_line_pos]; }
    void               define_a_macro(String name, String value);
    auto               find_a_macro(Buffer &name, bool insert, String xname, String val) -> std::optional<size_t>;
    auto               find_lower_case(const CitationKey &s, int &n) -> BibEntry *;
    auto               find_similar(const CitationKey &s, int &n) -> BibEntry *;
    void               forward_pass();
    auto               get_class(codepoint c) -> id_type { return id_class[c.value]; }
    void               handle_multiple_entries(BibEntry *Y);
    void               kill_the_lists();
    auto               look_for_macro(const Buffer &name) -> std::optional<size_t>;
    auto               look_for_macro(size_t h, const std::string &name) -> std::optional<size_t>;
    void               mac_def_val(size_t X) { all_macros[X].set_default_value(); }
    void               mac_set_val(size_t X, std::string s) { all_macros[X].set_value(std::move(s)); }
    auto               make_entry(const CitationKey &a, bib_creator b, Istring myid) -> BibEntry *;
    auto               next_char() -> codepoint { return input_line[input_line_pos++]; }
    void               next_line(bool what);
    auto               not_start_or_end(int what, char c, bool s) -> bool;
    void               parse_one_item();
    void               parse_one_field(BibEntry *X);
    void               read_one_field(bool store);
    void               read_field(bool store);
    auto               read2(bib_from pre) -> bool;
    void               reset_input() { input_line.clear(); }
    void               reverse_pass();
    void               scan_for_at();
    auto               scan_identifier(size_t what) -> bool;
    auto               scan_identifier0(size_t what) -> int;
    auto               see_new_entry(entry_type cn, int lineno) -> BibEntry *;
    void               skip_space();
    [[nodiscard]] auto wrong_first_char(codepoint c, size_t what) const -> int;

public:
    [[nodiscard]] auto is_in_ra() const -> bool { return in_ra; }

    auto        get_an_entry(size_t i) { return all_entries[i]; }
    auto        exec_bibitem(const std::string &w, const std::string &b) -> Istring;
    void        nocitestar_true() { nocitestar = true; }
    auto        implement_cit(String x, std::string w) -> int;
    auto        is_year_string(const std::string &y, bib_from from) -> String;
    void        work();
    void        read(const std::string &src, bib_from ct);
    auto        read0(Buffer &B, bib_from ct) -> bool;
    void        read1(const std::string &cur);
    void        read_ra();
    void        err_in_file(String s, bool last) const;
    static void err_in_name(String a, long i);
    void        boot(std::string S, bool inra);
    void        enter_in_table(BibEntry *x) { all_entries_table.push_back(x); }
    void        bootagain();

    static void bad_year(const std::string &given, String wanted);
    static void err_in_entry(String a);
    static auto find_field_pos(const std::string &s) -> field_pos;
    static auto find_type(const std::string &s) -> entry_type;
    static auto wrong_class(int y, const std::string &Y, bib_from from) -> bool;
};

inline Bibtex *the_bibtex;

class Bbl {
private:
    Buffer        B;
    std::ofstream file;
    bool          too_late{false};

public:
    friend class BibEntry;

    std::string name;
    LinePtr     lines;

    void               newline();
    void               push_back(String s) { B.push_back(s); }
    void               push_back(const std::string &s) { B.push_back(s); }
    void               push_back_braced(const std::string &s) { B.push_back_braced(s); }
    auto               non_empty_buf() -> bool { return !B.empty(); }
    void               reset() { B.clear(); }
    void               reset_lines() { lines.clear(); }
    [[nodiscard]] auto is_too_late() const -> bool { return too_late; }
    void               finish() { too_late = true; } // \todo should this be called ~Bbl ?
    void               open() {
        if (!file.is_open()) file = tralics_ns::open_file(name, true);
    }
};
