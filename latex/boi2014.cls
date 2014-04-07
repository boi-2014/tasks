%%
%% LaTeX class definition for BOI 2014 problem statements
%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{boi2014}
\LoadClass[11pt,a4paper]{article}
\RequirePackage{a4wide}
\RequirePackage{amsmath}
\RequirePackage{calc}
\RequirePackage{fancyhdr}
\RequirePackage{float}
\RequirePackage{graphicx}
\RequirePackage[colorlinks,urlcolor=blue]{hyperref}
\RequirePackage[utf8x]{inputenc}
\RequirePackage{lastpage}
\RequirePackage{listings}
\RequirePackage{lmodern}
\RequirePackage{multirow}
\RequirePackage{pstricks}
\RequirePackage[compact]{titlesec}
\RequirePackage{verbatim}
\RequirePackage{wrapfig}

\pagestyle{fancy}

%%
%% Variables
%%

\newcommand{\DayNum}{}    % renew in task description
\newcommand{\TaskCode}{}  % renew in task description
\newcommand{\TaskName}{}  % renew in task description

%%
%% Strings
%%

\newcommand{\Language}{EN}  % renew in per language class files

\newcommand{\Olympiad}{Baltic Olympiad in Informatics}
\newcommand{\OlympiadDay}{Day \DayNum}
\newcommand{\LocationDate}{April 26--30, Palanga}

\newcommand{\PageOf}[2]{Page #1 of #2}

\newcommand{\TitleTask}{Task}
\newcommand{\TitleImplementation}{Implementation}
\newcommand{\TitleOutput}{Output}
\newcommand{\TitleInput}{Input}
\newcommand{\TitleExample}{Example}
\newcommand{\TitleExamples}{Examples}
\newcommand{\TitleScoring}{Scoring}
\newcommand{\TitleExplanation}{Comments}
\newcommand{\TitleConstraints}{Constraints}

%%
%% Page layout
%%

\newcommand{\Logo}{boi2014}
\newlength{\LogoLength}
\setlength{\LogoLength}{2.1cm}
\newlength{\LogoMargin}
\setlength{\LogoMargin}{3mm}

\lhead{}\rhead{}
\chead{%
    \begin{tabular}{@{}p{\LogoLength+\LogoMargin}@{}p{\textwidth-\LogoLength-\LogoMargin}@{}}%
        \begin{minipage}[b]{\LogoLength}%
            \includegraphics[width=\LogoLength]{\Logo}
        \end{minipage} &%
            \begin{minipage}[b]{\textwidth-\LogoLength-\LogoMargin}%
            {\sffamily\Large
                \Olympiad%
                \hfill\makebox[0pt][r]{\OlympiadDay}}
            \vskip 2.5mm \hrule\vskip 2.5mm%
            {\sffamily\makebox[0pt][l]{%
                \LocationDate}%
            \hfill\ttfamily\bfseries\makebox[0pt][r]{\TaskCode\enskip$\bullet$\enskip\Language}}
        \end{minipage}%
    \end{tabular}%
}
\lfoot{}\rfoot{}
\cfoot{\small
	\makebox[0pt][r]{\PageOf{\thepage}{\pageref*{LastPage}}}}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}

%%
%% Headings
%%

\newcommand\Task{\section*{\TitleTask}}
\newcommand\Implementation{\section*{\TitleImplementation}}
\newcommand\Input{\section*{\TitleInput}}
\newcommand\Output{\section*{\TitleOutput}}
\newcommand\Example{\section*{\TitleExample}}
\newcommand\Examples{\section*{\TitleExamples}}
\newcommand\Scoring{\section*{\TitleScoring}}
\newcommand\Constraints{\section*{\TitleConstraints}}
\newcommand\Extra{\section*{\TitleExtra}}

%%
%% Body
%%

\newcommand{\taskheadline}[1]{{\bfseries\LARGE\noindent#1\par}}
\AtBeginDocument{
    \headheight=50pt%
    \headsep=14pt%
    \taskheadline{\TaskName}%
    \parindent=0pt%
    \parskip=6pt
}

\newcommand\example[3]{% need a flexible way to change column widths
    \begin{tabular}{|p{4cm}|p{3cm}|p{7.2cm}|}
        \hline
        {\bf\TitleInput} & {\bf\TitleOutput} & {\bf\TitleExplanation} \\
        \hline
        {\tt#1} & {\tt#2} & {#3} \\
        \hline
    \end{tabular}}
\newcommand\exampleflex[4]{% need a flexible way to change column widths
    \begin{tabular}{#1}
        \hline
        {\bf\TitleInput} & {\bf\TitleOutput} & {\bf\TitleExplanation} \\
        \hline
        {\tt#2} & {\tt#3} & {#4} \\
        \hline
    \end{tabular}}
\newcommand\rawexample[3]{%
    \begin{tabular}{|p{5cm}|p{4cm}|}
        \hline
        {\bf\TitleInput} & {\bf\TitleOutput} \\
        \hline
        {\tt#1} & {\tt#2} \\
        \hline
    \end{tabular}}
\newcommand\rawexampleflex[3]{%
    \begin{tabular}{#1}
        \hline
        {\bf\TitleInput} & {\bf\TitleOutput} \\
        \hline
        {\tt#2} & {\tt#3} \\
        \hline
    \end{tabular}}

\newcommand\includefile[1]{
    \vspace{-1.5em}\verbatiminput{#1}}
