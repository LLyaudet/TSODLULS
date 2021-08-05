#This file is part of TSODLULS library.
#
#TSODLULS is free software: you can redistribute it and/or modify
#it under the terms of the GNU Lesser General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#TSODLULS is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Lesser General Public License for more details.
#
#You should have received a copy of the GNU Lesser General Public License
#along with TSODLULS.  If not, see <http://www.gnu.org/licenses/>.
#
#©Copyright 2018-2021 Laurent Lyaudet

.PHONY: clean


#-----------------------------------------------------------
#Build latex article
#-----------------------------------------------------------
build: ./TSODL_for_C_1_0_0.pdf

./TSODL_for_C_1_0_0.pdf: ./TSODL_for_C_1_0_0.tex ./TSODL_for_C_1_0_0.bib
	pdflatex ./TSODL_for_C_1_0_0.tex
	bibtex ./TSODL_for_C_1_0_0.aux
	pdflatex ./TSODL_for_C_1_0_0.tex
	pdflatex ./TSODL_for_C_1_0_0.tex

#-----------------------------------------------------------
#Clean
#-----------------------------------------------------------
clean:
	rm -f ./*.log ./*.out ./*.aux ./*.bbl ./*.blg ./*.toc ./*.snm ./*.nav

soft-clean:
	rm -f ./*.log ./*.out ./*.aux ./*.blg ./*.toc ./*.snm ./*.nav
