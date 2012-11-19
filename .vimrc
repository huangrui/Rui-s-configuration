let g:winManagerWindowLayout='FileExplorer|TagList'
nmap wm :WMToggle<cr>
set t_Co=256

"if has("cscope")
"      	set csprg=/usr/local/bin/cscope
"	set csto=0
"   	set cst
"        set nocsverb
"	if filereadable("cscope.out")
"		cs add cscope.out
"	elseif $CSCOPE_DB != ""
"		cs add $CSCOPE_DB
"      	endif
"    	set csverb
"endif

"set cscopequickfix=s-,c-,d-,i-,t-,e-

set nu
set is
set tw=70 fo+=Mm
set pastetoggle=<F12>
map <silent><F6> :NEXTCOLOR<cr>
map <silent><F5> :PREVCOLOR<cr>

" Capitalize words and regions easily
" http://vim.wikia.com/wiki/Capitalize_words_and_regions_easily

if (&tildeop)
  nmap gcw guw~l
  nmap gcW guW~l
  nmap gciw guiw~l
  nmap gciW guiW~l
  nmap gcis guis~l
  nmap gc$ gu$~l
  nmap gcgc guu~l
  nmap gcc guu~l
  vmap gc gu~l
else
  nmap gcw guw~h
  nmap gcW guW~h
  nmap gciw guiw~h
  nmap gciW guiW~h
  nmap gcis guis~h
  nmap gc$ gu$~h
  nmap gcgc guu~h
  nmap gcc guu~h
  vmap gc gu~h
endif

filetype plugin indent on
set completeopt=longest,menu,
color desert
