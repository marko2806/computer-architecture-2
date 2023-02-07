  .intel_syntax noprefix
  .global potprogram_asm
  
potprogram_asm:
    mov ecx, 0            /*brojac*/
    mov eax, 0            /*rezultat*/
    mov edx, [esp + 4]    /*granica*/
 
add_nums: 
    add eax, ecx          /* u prvom prolasku prije provjere uvjeta zbrajaju se 0 + 0*/
    add ecx, 1
    cmp ecx,edx
    jl add_nums
end:
    ret
