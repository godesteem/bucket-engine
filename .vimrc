" File              : .vimrc
" Author            : Philipp Zettl <philipp.zettl@godesteem.de>
" Date              : 28.09.2019
" Last Modified Date: 23.02.2020
" Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>

" Requirements:
" NERDTree
" Syntastic
" vim-header

set shiftwidth=2
set softtabstop=2
set expandtab

let g:header_auto_add_header = 1
let g:header_field_author = "Philipp Zettl"
let g:header_field_author_email = "philipp.zettl@godesteem.de"
let NERDTreeShowHidden = 1

" C++ Settings "
let g:syntastic_cpp_check_header = 1
let g:syntastic_cpp_auto_refresh_includes = 1

let g:syntastic_cpp_include_dirs = ['engine/src', 'engine/vendor', 'engine/vendor/spdlog/include/spdlog', 'engine/vendor/glad/include', 'engine/vendor/imgui']
let g:syntastic_cpp_compiler_options = ' -std=c++17'
let g:syntastic_cpp_compiler = 'clang++'

nnoremap <F5> :!./build.sh<CR>
nnoremap <C-t> :tabedit %<CR>


map <F4> :AddGNULicense<CR>
