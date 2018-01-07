@dnl = internal constant [4 x i8] c"%d\0A\00"
@fnl = internal constant [6 x i8] c"%.1f\0A\00"
@d   = internal constant [3 x i8] c"%d\00"	
@lf  = internal constant [4 x i8] c"%lf\00"	

declare i32 @printf(i8*, ...) 
declare i32 @scanf(i8*, ...)
declare i32 @puts(i8*)

define void @printInt(i32 %x) {
       %t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0
       call i32 (i8*, ...) @printf(i8* %t0, i32 %x) 
       ret void
}

define void @printDouble(double %x) {
entry: %t0 = getelementptr [6 x i8], [6 x i8]* @fnl, i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %t0, double %x) 
	ret void
}

define void @printString(i8* %s) {
entry:  call i32 @puts(i8* %s)
	ret void
}

define i32 @readInt() {
entry:	%res = alloca i32
        %t1 = getelementptr [3 x i8], [3 x i8]* @d, i32 0, i32 0
	call i32 (i8*, ...) @scanf(i8* %t1, i32* %res)
	%t2 = load i32, i32* %res
	ret i32 %t2
}

define double @readDouble() {
entry:	%res = alloca double
        %t1 = getelementptr [4 x i8],[4 x i8]* @lf, i32 0, i32 0
	call i32 (i8*, ...) @scanf(i8* %t1, double* %res)
	%t2 = load double, double* %res
	ret double %t2
}

define i8* @___stringConcat(i8* nocapture readonly, i8* nocapture readonly) {
  %3 = tail call i64 @strlen(i8* %0) #3
  %4 = tail call i64 @strlen(i8* %1) #3
  %5 = add i64 %3, 1
  %6 = add i64 %5, %4
  %7 = tail call noalias i8* @malloc(i64 %6) #4
  %8 = tail call i8* @strcpy(i8* %7, i8* %0) #4
  %9 = tail call i8* @strcat(i8* %7, i8* %1) #4
  ret i8* %7
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64)

; Function Attrs: argmemonly nounwind readonly
declare i64 @strlen(i8* nocapture)

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8* nocapture readonly)

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8* nocapture readonly)
