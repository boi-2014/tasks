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
\RequirePackage{placeins}
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
\newcommand{\TitleExperimentation}{Experimentation}

%%
%% Shorthands
%%

\newcommand{\includefile}[1]{\vspace{-1.5em}\verbatiminput{#1}}
\newcommand{\method}[1]{{\tt #1}}

%%
%% Page layout
%%

\newcommand{\Logo}{boi2014-bw}
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

\newcommand\Task{\FloatBarrier\section*{\TitleTask}}
\newcommand\Implementation{\FloatBarrier\section*{\TitleImplementation}}
\newcommand\Input{\FloatBarrier\section*{\TitleInput}}
\newcommand\Output{\FloatBarrier\section*{\TitleOutput}}
\newcommand\Example{\FloatBarrier\section*{\TitleExample}}
\newcommand\Examples{\FloatBarrier\section*{\TitleExamples}}
\newcommand\Scoring{\FloatBarrier\section*{\TitleScoring}}
\newcommand\Constraints{\FloatBarrier\section*{\TitleConstraints}}
\newcommand\Experimentation{\FloatBarrier\section*{\TitleExperimentation}}
\newcommand\Extra{\FloatBarrier\section*{\TitleExtra}}


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

\newcommand\simpleexample[2]{% need a flexible way to change column widths
    \renewcommand{\arraystretch}{1.5}
    \begin{figure}[h!]
        \begin{tabular}{|p{4cm}|p{3cm}|}
            \hline
            {\bf\TitleInput} & {\bf\TitleOutput} \\
            \hline
            {\tt#1} & {\tt#2} \\
            \hline
        \end{tabular}
    \end{figure}
}
\newcommand\example[3]{% need a flexible way to change column widths
    \renewcommand{\arraystretch}{1.5}
    \begin{figure}[h!]
        \begin{tabular}{|p{3.5cm}|p{3.5cm}|p{7.2cm}|}
            \hline
            {\bf\TitleInput} & {\bf\TitleOutput} & {\bf\TitleExplanation} \\
            \hline
            {\tt#1} & {\tt#2} & {#3} \\
            \hline
        \end{tabular}
    \end{figure}
}
