forfiles -p \PopHead\logs -s -m *.txt /D -2 /C "cmd /c Del @path && echo @path" 
