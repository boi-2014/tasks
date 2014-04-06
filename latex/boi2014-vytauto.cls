%%
%% LaTeX class definition for BOI 2014 task statements
%%
%% Version (last updated): 2014-4-6 16:55

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{boi2014}
\LoadClass[11pt,a4paper]{article}
\RequirePackage{ifthen}
\RequirePackage[utf8x]{inputenc}
\RequirePackage{times}
\RequirePackage{a4wide}
\RequirePackage{graphicx}
\RequirePackage{wrapfig}
\RequirePackage{pstricks}
\RequirePackage{calc}
\RequirePackage{ifthen}
\RequirePackage{fancyhdr}
\RequirePackage{lastpage}
\RequirePackage{times}
\RequirePackage{verbatim}
\RequirePackage{listings}
\RequirePackage{amsmath}
\RequirePackage[sf,sl,topmarks]{titlesec}
\RequirePackage[lithuanian]{babel}
\RequirePackage{lmodern}
\RequirePackage{framed}
\RequirePackage{float}

\pagestyle{fancy}

% Things below are specific to littex, i.e. font encoding
% and using Courier as fixed-width font instead of cmr family.
% Might want to try XeTeX one day.
\def\LTfontencoding{L7x}
\usepackage[\LTfontencoding]{fontenc}
\renewcommand{\sfdefault}{uhv}
%\renewcommand{\rmdefault}{utm}
%\renewcommand{\ttdefault}{ucr}

%%
%% Variables
%%

\newcommand{\taskname}{}     % renew in taskdescription
\newcommand{\longtaskname}{} % renew in taskdescription
\newcommand{\taskgroup}{}    % renew in taskdescription
\newcommand{\version}{1.0}   % not used at the moment
\newcommand{\stageid}{}     % renew in taskdescription

%%
%% Strings
%%

\newcommand{\Olympiad}{Baltic Olympiad in Informatics}
\newcommand{\Date}{April 26--30, 2014}
\newcommand{\Location}{Palanga, Lithuania}

\newcommand{\Firstday}{Day 1}
\newcommand{\Secondday}{Day 2}
\newcommand{\Practiceday}{Day 0}

\newcommand{\Day}{}

\newcommand{\PageOf}[2]{Page #1 out of #2}
\newcommand{\TitleTask}{Task}
\newcommand{\TitleImplementation}{Implementation}
\newcommand{\TitleOutput}{Output}
\newcommand{\TitleInput}{Input}
\newcommand{\TitleExample}{Example}
\newcommand{\TitleExamples}{Examples}
\newcommand{\TitleSubtasks}{Subtasks}
\newcommand{\TitleDetails}{Details}
\newcommand{\TitleExplanation}{Comments}
\newcommand{\TitleConstraints}{Constraints}
\newcommand{\TitleGrading}{Partial Scoring}

%%
%% Environments
%%

\newenvironment{todo}{\begin{framed} \centering}{\end{framed}}

%%
%% Page layout
%%

%\overfullrule=3pt
%\showboxdepth=2
%\showboxbreadth=50

\newlength{\LogoLength}\setlength{\LogoLength}{2.1cm}
\newcommand{\Logo}{logo-bw}

%\newcommand{\delimiter}{\enskip$\bullet$\enskip}
\newcommand{\Delimiter}{\enskip$\bullet$\enskip}

\lhead{}\rhead{}
\chead{%
    \begin{tabular}{@{}p{\LogoLength+5mm}@{}p{\textwidth-\LogoLength-5mm}@{}}%
    \begin{minipage}[b]{\LogoLength}%
    \includegraphics[width=\LogoLength]{\Logo}
    \end{minipage} &%
    \begin{minipage}[b]{\textwidth-\LogoLength-5mm}%
    {\sffamily\Large\Olympiad}
    \vskip 2mm \hrule\vskip 2mm%
    {\sffamily\makebox[0pt][l]{%
        \Day%
        \ifthenelse{\equal\Day{} \or \(\equal\Date{} \and
                    \equal\Location{}\)}{}{\Delimiter}%
        \Date%
        \ifthenelse{\equal\Date{} \or \equal\Location{}}{}{\Delimiter}%
        \Location%
    }
    \hfill\ttfamily\bfseries\makebox[0pt][r]{\taskname}}%
    \end{minipage}%
    \end{tabular}%
}
\lfoot{}\rfoot{}
\cfoot{\small
	\makebox[0pt][r]{\PageOf{\thepage}{\pageref{LastPage}}}}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}

%%
%% Headings
%%

\newcommand\periodafter[1]{#1.}
\newcommand\newsec[2]%
  {\titleformat{#1}[#2]%
    {\normalfont\bfseries}{\thesection.}{1em}{\periodafter}%
   \titlespacing*{#1}{0pt}{10pt}{1.5ex plus .2ex}}

\newsec{\section}{runin}
\newsec{\subsection}{block} % quick ugly hack

\newcommand\Task{\section*{\TitleTask}}
\newcommand\Implementation{\section*{\TitleImplementation}}
\newcommand\Input{\section*{\TitleInput}}
\newcommand\Output{\section*{\TitleOutput}}
\newcommand\Example{\subsection*{\TitleExample}}
\newcommand\Examples{\subsection*{\TitleExamples}}
\newcommand\Subtasks{\subsection*{\TitleSubtasks}}
\newcommand\Details{\subsection*{\TitleDetails}}
\newcommand\Grading{\section*{\TitleGrading}}
\newcommand\Constraints{\section*{\TitleConstraints}}
\newcommand\Extra{\section*{\TitleExtra}}

%%
%% Body
%%

\newcommand{\taskheadline}[1]{{\bfseries\LARGE\noindent#1\par}}
\AtBeginDocument{
    \headheight=50pt%
    \headsep=14pt%
    \taskheadline{\longtaskname}%
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
\newcommand\rawexample[3]{%
    \begin{tabular}{|p{5cm}|p{4cm}|}
        \hline
        {\bf\TitleInput} & {\bf\TitleOutput} \\
        \hline
        {\tt#1} & {\tt#2} \\
        \hline
    \end{tabular}}
\newcommand\includefile[1]{
    \vspace{-1.5em}\verbatiminput{#1}}

% vi: ts=4 sw=4 enc=utf-8

