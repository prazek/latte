@dnl = internal constant [4 x i8] c"%d\0A\00"
@fnl = internal constant [6 x i8] c"%.1f\0A\00"
@d   = internal constant [3 x i8] c"%d\00"	
@lf  = internal constant [4 x i8] c"%lf\00"	

declare i32 @printf(i8*, ...) 
declare i32 @scanf(i8*, ...)
declare i32 @puts(i8* nocapture readonly)

define void @printInt(i32 %x) {
       %t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0
       call i32 (i8*, ...) @printf(i8* %t0, i32 %x) 
       ret void
}

define void @printString(i8* %s) {
entry:  call i32 @puts(i8* %s)
	ret void
}

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c" \00", align 1
@stdin = external global %struct._IO_FILE*, align 8
@.str.2 = private unnamed_addr constant [7 x i8] c"%s, %s\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @readInt() #0 {
  %1 = alloca i32, align 4
  %2 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32* %1)
  %3 = load i32, i32* %1, align 4
  ret i32 %3
}

declare i32 @__isoc99_scanf(i8*, ...)

; Function Attrs: noinline nounwind optnone uwtable
define i8* @readString() {
  %1 = alloca i8*, align 8
  %2 = alloca i64, align 8
  %3 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  store i8* null, i8** %1, align 8
  store i64 0, i64* %2, align 8
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8
  %5 = call i64 @getline(i8** %1, i64* %2, %struct._IO_FILE* %4)
  store i64 %5, i64* %2, align 8
  %6 = load i8*, i8** %1, align 8
  %7 = load i64, i64* %2, align 8
  %8 = sub i64 %7, 1
  %9 = getelementptr inbounds i8, i8* %6, i64 %8
  %10 = load i8, i8* %9, align 1
  %11 = sext i8 %10 to i32
  %12 = icmp eq i32 %11, 10
  br i1 %12, label %13, label %18

; <label>:13:                                     ; preds = %0
  %14 = load i8*, i8** %1, align 8
  %15 = load i64, i64* %2, align 8
  %16 = sub i64 %15, 1
  %17 = getelementptr inbounds i8, i8* %14, i64 %16
  store i8 0, i8* %17, align 1
  br label %18

; <label>:18:                                     ; preds = %13, %0
  %19 = load i8*, i8** %1, align 8
  ret i8* %19
}

define i8* @___stringConcat(i8* nocapture readonly, i8* nocapture readonly) {
  %3 = tail call i64 @strlen(i8* %0)
  %4 = tail call i64 @strlen(i8* %1)
  %5 = add i64 %3, 1
  %6 = add i64 %5, %4
  %7 = tail call noalias i8* @malloc(i64 %6)
  %8 = tail call i8* @strcpy(i8* %7, i8* %0)
  %9 = tail call i8* @strcat(i8* %7, i8* %1)
  ret i8* %7
}

declare i64 @getline(i8**, i64*, %struct._IO_FILE*)

@.runtimeError = private unnamed_addr constant [15 x i8] c"Runtime error\0A\00", align 1

; Function Attrs: noreturn nounwind uwtable
define void @error() {
  %1 = tail call i32 @puts(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.runtimeError, i64 0, i64 0))
  tail call void @exit(i32 1)
  unreachable
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64)

; Function Attrs: argmemonly nounwind readonly
declare i64 @strlen(i8* nocapture)

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8* nocapture readonly)

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8* nocapture readonly)

; Function Attrs: nounwind
declare i32 @getc(%struct._IO_FILE* nocapture)

; Function Attrs: nounwind
declare noalias i8* @realloc(i8* nocapture, i64)

; Function Attrs: nounwind
declare void @free(i8* nocapture)

declare void @exit(i32) noreturn


;define double @readDouble() {
;entry:	%res = alloca double
;        %t1 = getelementptr [4 x i8],[4 x i8]* @lf, i32 0, i32 0;
;	call i32 (i8*, ...) @scanf(i8* %t1, double* %res)
;	%t2 = load double, double* %res
;	ret double %t2
;}
;
;define void @printDouble(double %x) {
;entry: %t0 = getelementptr [6 x i8], [6 x i8]* @fnl, i32 0, i32 0
;	call i32 (i8*, ...) @printf(i8* %t0, double %x)
;	ret void
;}
