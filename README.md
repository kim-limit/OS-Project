# OS_TEAM_PROJECT

## ✅ 사용법

### build

<pre>make</pre>

### clean

<pre>make clean</pre>

### run

<pre>make run</pre>

## ✅ 명령어 종류

### cli창 비우기 (clear, cls)

<pre>clear or cls</pre>

### 폴더 생성하기 (mkdir)

<pre>mkdir [폴더이름 ...]
mkdir -m 777 [폴더이름] // 권한 설정하면서 생성
mkdir -p /경로/폴더이름 // 상위 폴더도 같이 생성
</pre>

### 파일 생성하기 (touch)

<pre>touch [파일이름]
touch -t mdhm [파일이름] // 생성시간 변경 
ex) touch -t 11111230 newfile
touch -m [파일 이름] // 서버시간으로 변경
</pre>

### 복사 (cp)

<pre>
 cp [복사할 파일 이름] [생성할 파일 이름] // 파일 복사
 cp -r [복사할 폴더 이름] [생성할 폴더 이름] // 폴더 복사
</pre>

### 파일 삭제 (rm)

<pre>
rm [삭제할 파일 이름]
rm -f [삭제할 파일 이름] // 파일 없어도 메세지 x
rm -r [삭제할 폴더 이름] // 하위 폴더도 다삭제
</pre>

### 경로 이동 (cd)

<pre>
cd [경로] or / or ..
..하면 이전 경로로 이동
/ 는 홈디렉토리로 이동
</pre>

### 현재 경로 확인 (pwd)

<pre>pwd</pre>

### 현재 있는 내용 리스트 출력 (ls)

<pre>
ls
-a 숨김파일도 출력
-l 긴 목록으로 출력
-al도 됨
</pre>

### txt파일 읽기 (cat)

<pre>
cat [파일.txt] 
-b, -n 하면 앞에 숫자 붙음
cat > [파일] // txt파일 생성 (마지막에 :wq 하면 끝)
</pre>

### 권한 변경 (chmod)

<pre>
chmod [8진수 세자리] [파일 or 폴더명]
-R 붙으면 하위까지
</pre>

### 파일 찾기 (find)

<pre>
find [파일 or 폴더명]
</pre>

## 종료 (exit)

<pre>
exit
</pre>
