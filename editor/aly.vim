" Aly Language created syntax highlighting in Vimscript
" Language: Aly
" Latest Revision: 06-08-2025

if exists("b:current_syntax")
  finish
endif

let s:cpo_save = &cpo
setlocal cpo&vim

let s:aly_syntax_keywords = {
      \ 'alyKeywords': [
      \   'if',
      \   'else'
      \ ],
      \ 'alyType': [
      \   'integer'
      \ ]
      \ }

function! s:syntax_keyword(dict)
  for key in keys(a:dict)
    execute 'syntax keyword' key join(a:dict[key], ' ')
  endfor
endfunction

call s:syntax_keyword(s:aly_syntax_keywords)

syntax region alyCommentLine1 start=";" end="$"
syntax region alyCommentLine2 start="#" end="$"

delfunction s:syntax_keyword

highlight default link alyKeywords Keyword
highlight default link alyType Type
highlight default link alyCommentLine1 Comment
highlight default link alyCommentLine2 Comment

let b:current_syntax = "aly"

let &cpo = s:cpo_save
unlet! s:cpo_save
