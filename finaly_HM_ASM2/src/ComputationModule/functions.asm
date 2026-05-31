section .data
    one         dq 1.0
    two         dq 2.0
    three       dq 3.0
    four        dq 4.0
    minus_eight dq -8.0
    ln2_neg     dq -0.6931471805599453 

global value_f1:function
global value_f2:function
global value_f3:function
global df_f1:function
global df_f2:function
global df_f3:function

section .text

;-----------------------------------
; value_f1
; Computes f1(x) = 1 + 4 / (x^2 + 1)
;
; EXPECTS: [EBP + 8] = double x
;
; DESTROYS: NONE
;
; RETURNS: ST0 = f1(x)
;  
;-----------------------------------
value_f1: 
    push ebp
    mov ebp, esp 
    
    fld qword [ebp + 8]      
    fmul st0, st0           
    fadd qword [one]        
    
    fld qword [four]         
    fdivrp st1, st0          
    
    fadd qword [one]       
    
    pop ebp 
    ret 

;-----------------------------------
; value_f2
; Computes f2(x) = x^3
;
; EXPECTS: [EBP + 8] = double x
;
; DESTROYS: NONE 
;
; RETURNS: ST0
;   
;-----------------------------------
value_f2:
    push ebp 
    mov ebp, esp 
    
    fld qword [ebp + 8]      
    fmul st0, st0           
    fmul qword [ebp + 8]    
    
    pop ebp 
    ret 

;-----------------------------------
; value_f3
; Computes f3(x) = 2^(-x)
;
; EXPECTS: EBP + 8] = double x
;
; DESTROYS: NONE
;
; RETURNS: ST0
;   
;-----------------------------------
value_f3:
    push ebp 
    mov ebp, esp 
    
    fld qword [ebp + 8]     
    fchs                     
    
    fld st0                 
    frndint                  
    fxch st1                
    fsub st0, st1           
    
    f2xm1                    
    fld1                    
    faddp st1, st0         
    
    fscale                   
    fstp st1                
    
    pop ebp
    ret 
;-----------------------------------
; df_f1
; Computes f1'(x) = -8x / (x^2 + 1)^2
;
; EXPECTS: EBP + 8] = double x
;
; DESTROYS: NONE 
;
; RETURNS: ST0
;
;-----------------------------------
df_f1:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]      
    fmul qword [minus_eight] 
    
    fld qword [ebp + 8]     
    fmul st0, st0            
    fadd qword [one]        
    fmul st0, st0            
    
    fdivp st1, st0           
    
    pop ebp
    ret
;-----------------------------------
; df_f2
; Computes f2'(x) = 3x^2
;
; EXPECTS: [EBP + 8] = double x
;
; DESTROYS: NONE
;
; RETURNS: ST0
;   
;-----------------------------------
df_f2:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]     
    fmul st0, st0            
    fmul qword [three]       
    
    pop ebp
    ret
;-----------------------------------
; df_f3
; Computes f3'(x) = -ln(2) * 2^(-x)
;
; EXPECTS: [EBP + 8] = double x
;
; DESTROYS: NONE
;
; RETURNS: ST0
;
;-----------------------------------
df_f3:
    push ebp                 
    mov ebp, esp
    
    fld qword [ebp + 8]      
    fchs                    
    
    fld st0                  
    frndint                 
    fxch st1                
    fsub st0, st1            
    f2xm1                   
    fld1                   
    faddp st1, st0          
    
    fscale                 
    fstp st1                 
    
    fmul qword [ln2_neg]     
    
    pop ebp
    ret
