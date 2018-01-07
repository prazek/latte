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

;define double @readDouble() {
;entry:	%res = alloca double
;        %t1 = getelementptr [4 x i8],[4 x i8]* @lf, i32 0, i32 0;
;	call i32 (i8*, ...) @scanf(i8* %t1, double* %res)
;	%t2 = load double, double* %res
;	ret double %t2
;}

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
@stdin = external global %struct._IO_FILE*, align 8

define noalias i8* @readString() {
  br label %1

; <label>:1:                                      ; preds = %0, %17
  %2 = phi i64 [ 0, %0 ], [ %21, %17 ]
  %3 = phi i64 [ 0, %0 ], [ %19, %17 ]
  %4 = phi i8* [ null, %0 ], [ %18, %17 ]
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8
  %6 = tail call i32 @getc(%struct._IO_FILE* %5)
  %7 = icmp eq i32 %6, -1
  %8 = icmp eq i32 %6, 10
  %9 = or i1 %7, %8
  %10 = select i1 %9, i32 0, i32 %6
  %11 = icmp ugt i64 %3, %2
  br i1 %11, label %17, label %12

; <label>:12:                                     ; preds = %1
  %13 = add i64 %3, 10
  %14 = tail call i8* @realloc(i8* %4, i64 %13)
  %15 = icmp eq i8* %14, null
  br i1 %15, label %16, label %17

; <label>:16:                                     ; preds = %12
  tail call void @free(i8* %4) #4
  br label %24

; <label>:17:                                     ; preds = %12, %1
  %18 = phi i8* [ %4, %1 ], [ %14, %12 ]
  %19 = phi i64 [ %3, %1 ], [ %13, %12 ]
  %20 = trunc i32 %10 to i8
  %21 = add i64 %2, 1
  %22 = getelementptr inbounds i8, i8* %18, i64 %2
  store i8 %20, i8* %22, align 1
  %23 = icmp eq i32 %10, 0
  br i1 %23, label %24, label %1

; <label>:24:                                     ; preds = %17, %16
  %25 = phi i8* [ null, %16 ], [ %18, %17 ]
  ret i8* %25
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

; Function Attrs: nounwind
declare i32 @getc(%struct._IO_FILE* nocapture)

; Function Attrs: nounwind
declare noalias i8* @realloc(i8* nocapture, i64)

; Function Attrs: nounwind
declare void @free(i8* nocapture)