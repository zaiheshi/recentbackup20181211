#! /usr/bin/env python
#coding=utf-8
from fpdf import FPDF, HTMLMixin
import re



f = open('result.txt', 'r')
content = f.read()
f.close()
keywords = ['TITLE', 'AUTHOR', 'ABSTRACT', 'ITEM']
lst_basic = []
for k in keywords:
    lst_basic.append(re.compile(r'\+\[(' + k + r')\]\n\s+\+([a-zA-Z\s\.\,\:\']+)\n').findall(content))

p_section = re.compile(r'\+\[(SECTION)\]\(([a-zA-Z\s]+)\)\n\s+\+([a-zA-Z\s\.\,\:\']+)\n')
section = p_section.findall(content)

p_subsection = re.compile(r'\+\[(SUBSECTION)\]\(([a-zA-Z\s]+)\)\n\s+\+([a-zA-Z\s\.\,\:\']+)\n')
subsection = p_subsection.findall(content)
# for i in lst_basic:
#     print(i)

TITLE = '''<H1 align="center">''' + lst_basic[0][0][1] + '''</H1>'''
AUTHOR = '''<H4 align="center">''' + lst_basic[1][0][1] + '''</H4>'''
ABSTRACT = '''<H4 align="center"><font size=10>''' + lst_basic[2][0][0] + '''</font></H4><font size=8><i>''' + lst_basic[2][0][1] + '''</i></font>'''
SECTION = ''''''
SUBSECTION=''''''

cc = 1
for i in range(len(section)):
    SECTION = SECTION + '''<br><b>'''+ str(cc) + "    "+section[i][1] + '''</b>''' + '''<p>''' + section[i][2] + '''</p>'''
    cc += 1

cc -= 1
dd = 1
for i in range(len(subsection)):
    SUBSECTION = SUBSECTION + '''<br><b><i>'''+ str(cc) + "." + str(dd) + "    " + subsection[i][1] + '''</i></b>''' + '''<p>''' + subsection[i][2] + '''</p>'''
    dd += 1

ITEM = '''<ul>'''

for i in range(len(lst_basic[3])):
    ITEM += '''<li>''' + lst_basic[3][i][1] + '''</li>'''
ITEM += '''</ul>'''

LAST = '''<p>The first thing you normally have is a title of the document, as well as information about the author and date of publication. In latex terms, this is all generally referred to</p>'''

html = TITLE + AUTHOR + ABSTRACT + SECTION + SUBSECTION + ITEM + LAST
class MyFPDF(FPDF, HTMLMixin):
    pass
pdf = MyFPDF()
# First page
pdf.add_page()
pdf.write_html(html)
pdf.output('html.pdf', 'F')



