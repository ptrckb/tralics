% -*- latex -*-
% $Id: amsmath.plt,v 2.38 2015/11/23 16:14:00 grimm Exp $
\ProvidesPackage{amsmath}[2015/11/13 v1.7 AMS math features for Tralics]


\DeclareOption{leqno}{\XMLaddatt[1]{equation-number}{left}}
\DeclareOption{reqno}{\XMLaddatt[1]{equation-number}{right}}
\DeclareOption{fleqn}{\XMLaddatt[1]{flushed-equation}{true}}

\DeclareOption{intlimits}{\let\ilimits@\displaylimits}
\DeclareOption{nointlimits}{\let\ilimits@\nolimits}

\DeclareOption{sumlimits}{\let\slimits@\displaylimits}
\DeclareOption{nosumlimits}{\let\slimits@\nolimits}
\DeclareOption{namelimits}{\PassOptionsToPackage{namelimits}{amsopn}}
\DeclareOption{nonamelimits}{\PassOptionsToPackage{nonamelimits}{amsopn}}
\newif\ifctagsplit@
\DeclareOption{centertags}{\ctagsplit@true}
\DeclareOption{tbtags}{\ctagsplit@false}
\DeclareOption{cmex10}{}
\DeclareOption{?}{}
\ExecuteOptions{nointlimits,sumlimits,namelimits,centertags}
\ProcessOptions\par


\def\choose{\atopwithdelims()}
\def\brack{\atopwithdelims[]}
\def\brace{\atopwithdelims\{\}}
\def\shoveleft{\multicolumn{1}{l}}
\def\shoveright{\multicolumn{1}{r}}
\def\mathpalette#1#2{\mathchoice {#1\displaystyle {#2}}%
{#1\textstyle {#2}}{#1\scriptstyle{#2}}{#1\scriptscriptstyle{#2}}}


\ifctagsplit@\else \XMLaddatt[1]{split-tags}{tb} \fi

% \RequirePackage{amstext}[2007/01/01]   % not needed
\RequirePackage{amsbsy}[2007/01/01]
\RequirePackage{amsopn}[2007/01/01]
\providecommand{\AmS}{AMS}
\def\Hat{\hat}
\def\Check{\check}
\def\Tilde{\tilde}
\def\Acute{\acute}
\def\Grave{\grave}
\def\Dot{\dot}
\def\Ddot{\ddot}
\def\Breve{\breve}
\def\Bar{\bar}
\def\Vec{\vec}

\def\UnimplementedOperator#1{\UnimplementedOperatorAux} 
\def\ams@unimp#1{\def#1{\UnimplementedOperator #1}}
%\def\ams@unimp{\mathbox{mstyle}[color][red]{X}}

\def\Bbbk{\mathbb{k}}

\newlength\mathindent
\newskip\multlinegap

\newcount\c@MaxMatrixCols \c@MaxMatrixCols=10  % 

\def\DeclareMathAlphabet#1#2#3#4#5{\a@define#1}
\def\DeclareMathSymbol#1#2#3#4{\a@define#1}
\def\a@define#1{\ifdefined#1 \else\let#1\relax\fi}

\newcommand\hdotsfor[2][]{%
  \ifcase #2 \or\dots\or\dots&\dots
  \or\dots&\dots&\dots\or\dots&\dots&\dots&\dots
  \or\dots&\dots&\dots&\dots&\dots\or\dots&\dots&\dots&\dots&\dots&\dots
  \or\dots&\dots&\dots&\dots&\dots\or\dots&\dots&\dots&\dots&\dots&\dots
  \or\dots&\dots&\dots&\dots&\dots&\dots&\dots
  \or\dots&\dots&\dots&\dots&\dots&\dots&\dots&\dots\fi
}


%% Objects that are not yet defined but described in the Book


% Command used by T. Bouche
% \equalenv{foo}{bar} is \let\foo\bar\let\endfoo\endbar
\providecommand\equalenv[2]{%
 \@ifundefined{#1}{\@xp\let\csname #1\@xp\endcsname\csname#2\endcsname
   \@xp\let\csname end#1\@xp\endcsname\csname end#2\endcsname}
 {\message{#1 already defined: I won't redefine it!^^J}}}

\newcommand\substack[1]{\begin{array}{c}#1\end{array}}
\newenvironment{subarray}[1]
{\bgroup\scriptstyle\begin{matrix}} {\end{matrix}\egroup}
\newenvironment{smallmatrix}{\begin{matrix}}{\end{matrix}}
%\def\intertext#1{\text{\let\vspace\@gobble#1}\\}
\def\intertext#1{\multicolumn{2}{l}{\text{\let\vspace\@gobble#1}}\\}
\def\displaybreak{}

\def\qed{\ensuremath{\Box}}


\def\minalignsep{0pt}

\DeclareRobustCommand{\tmspace}[3]{%
  \ifmmode\mskip#1#2\else\kern#1#3\fi\relax}
\newcommand{\negmedspace}{\tmspace-\medmuskip{.2222em}}
\newcommand{\negthickspace}{\tmspace-\thickmuskip{.2222em}}


%% Tags
\newcommand{\raisetag}[1]{} % no-op

%\def\@x@tag#1{\formulaattribute{tag}{(#1)}}
%\def\@y@tag#1{\formulaattribute{tag}{#1}}
%\def\x@tag#1{\qquad\mathrm{(#1)}}
%\def\y@tag#1{\qquad\mathrm{#1}}

\let\o@xtag\@xtag\let\o@ytag\@ytag  % make a copy
\let\ox@tag\x@tag\let\oy@tag\y@tag  % make a copy

\def\tagasattribute{%
  \let\@xtag\o@xtag\let\@ytag\o@ytag 
  \let\x@tag\@x@tag \let\y@tag\@y@tag}

\def\tagatendofformula{  
  \let\@xtag\o@xtag\let\@ytag\o@ytag 
  \let\x@tag\ox@tag \let\y@tag\oy@tag}

\def\tagatcurpos{%
  \let\@xtag\ox@tag\let\@ytag\oy@tag 
}
\tagatendofformula

% other commands


\def\sqrtsign{\sqrt}

\let\leftroot \@gobble
\let\uproot \@gobble

\let\bmdefine\def
\let\bm\mathbf
\def\boldmath{\mathversion{bold}}
\def\unboldmath{\mathversion{normal}}
\def\ibinom{\genfrac\lbrace\rbrace{0pt}{}}

\ams@unimp\bignplus
\ams@unimp\boxbar

% Table 8.13
\ams@unimp\bbslash
\ams@unimp\fatbslash
\ams@unimp\fatslash
\ams@unimp\lbag
\ams@unimp\rbag
\ams@unimp\minuso
\ams@unimp\moo
\ams@unimp\nplus
\ams@unimp\Ydown
\ams@unimp\Yup
\ams@unimp\Yleft
\ams@unimp\Yright

% table 8.15
\ams@unimp\ovee
\ams@unimp\owedge
\ams@unimp\varovee
\ams@unimp\varowedge

% Table 8.20
\ams@unimp\curlyveedownarrow
\ams@unimp\curlyveeuparrow
\ams@unimp\curlywedgeuparrow
\ams@unimp\curlywedgedownarrow
\ams@unimp\nnearrow
\ams@unimp\nnwarrow
\ams@unimp\ssearrow
\ams@unimp\sswarrow

% Table 8.22
\ams@unimp\Arrownot
\ams@unimp\Longarrownot
\ams@unimp\Mapsfromchar
\ams@unimp\Mapstochar
\ams@unimp\arrownot
\ams@unimp\longarrownot
\ams@unimp\mapsfromchar
\ams@unimp\mapstochar
\ams@unimp\lhook
%\ams@unimp\not
\ams@unimp\rhook

% Table 8.23
\ams@unimp\smallfrown
\ams@unimp\smallsmile
\ams@unimp\varpropto
\ams@unimp\shortmid
\ams@unimp\nshortmid
\ams@unimp\nshortparallel
\ams@unimp\shortparallel


% Table 8.27
\ams@unimp\llceil
\ams@unimp\rrceil
\ams@unimp\Lbag
\ams@unimp\Rbag
\ams@unimp\llfloor
\ams@unimp\rrfloor

\ams@unimp\nsucceq
\ams@unimp\npreceq
\ams@unimp\Lbag
\ams@unimp\Rbag
\ams@unimp\llceil
\ams@unimp\rrceil
\ams@unimp\leftrightarroweq

\ams@unimp\nsupseteqq
\ams@unimp\nsubseteqq
\ams@unimp\lvertneqq
\ams@unimp\gvertneqq
\ams@unimp\ntrianglelefteqslant
\ams@unimp\ntrianglerighteqslant
\ams@unimp\trianglelefteqslant
\ams@unimp\trianglerighteqslant
\ams@unimp\subsetplus
\ams@unimp\subsetpluseq
\ams@unimp\supsetplus
\ams@unimp\supsetpluseq
\ams@unimp\varsubsetneqq
\ams@unimp\varsubsetneq
\ams@unimp\varsupsetneqq
\ams@unimp\varsupsetneq
\ams@unimp\vartriangle
\ams@unimp\doublebarwedge

\let\ngeqq\ngeq
\let\nleqq\nleq 
\let\ngeqq\ngeq
\let\nleqq\nleq 
\let\ngeqslant\ngeq
\let\nleqslant\nleq



\endinput



