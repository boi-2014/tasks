%%
%% Lithuanian translations.
%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{boi2014-lt}

\LoadClass{boi2014}

% Things below are specific to littex, i.e. font encoding
\RequirePackage[lithuanian]{babel}
\def\LTfontencoding{L7x}
\usepackage[\LTfontencoding]{fontenc}

%%
%% Strings
%%

\renewcommand{\Language}{LT}

\renewcommand{\Olympiad}{Baltijos šalių informatikos olimpiada}
\renewcommand{\OlympiadDay}{\DayNum{} diena}
\renewcommand{\LocationDate}{Balandžio 26--30 d., Palanga}

\renewcommand{\PageOf}[2]{#1 puslapis iš #2}

\renewcommand{\TitleTask}{Užduotis}
\renewcommand{\TitleImplementation}{Realizacija}
\renewcommand{\TitleOutput}{Rezultatai}
\renewcommand{\TitleInput}{Pradiniai duomenys}
\renewcommand{\TitleExample}{Pavyzdys}
\renewcommand{\TitleExamples}{Pavyzdžiai}
\renewcommand{\TitleScoring}{Vertinimas}
\renewcommand{\TitleExplanation}{Komentarai}
\renewcommand{\TitleConstraints}{Ribojimai}
\renewcommand{\TitleExperimentation}{Eksperimentavimas}

\usepackage{fontspec}
\usepackage[lithuanian]{babel}
