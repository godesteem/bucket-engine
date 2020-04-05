" Requirements:
" NERDTree
" Syntastic
" vim-header

set shiftwidth=2
set softtabstop=2
set expandtab

let g:header_auto_add_header = 0
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
