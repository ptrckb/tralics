#pragma once
#include "tralics/enums.h"
#include <cstring>
#include <fstream>
#include <string>
#include <utility>

class Xml;

// -*- C++ -*-
// TRALICS, copyright (C) INRIA/apics (Jose' Grimm) 2006, 2007,2008

// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use,
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
// (See the file COPYING in the main directory for details)

// temporary for recursion.

// A class to count words... \todo where is that used? \todo chained list???
class WordList {
    WordList *  next;
    std::string name;
    size_t      hash;
    int         freq;

public:
    void               set_next(WordList *n) { next = n; }
    [[nodiscard]] auto next_empty() const -> bool { return next == nullptr; }
    WordList(std::string s, size_t h, WordList *N) : next(N), name(std::move(s)), hash(h), freq(1) {}
    [[nodiscard]] auto is_here(const std::string &s, size_t h) const -> bool { return (hash == h) && (name == s); }
    void               incr_freq() { freq++; }
    [[nodiscard]] auto get_freq() const -> int { return freq; }
    [[nodiscard]] auto get_next() const -> WordList * { return next; }
    auto               dump(std::ostream &X, int i) -> bool {
        if (freq == i) {
            X << freq << " " << name << "\n";
            return true;
        }
        return false;
    }
};
