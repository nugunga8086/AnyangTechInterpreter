sum = 0
println "아무 숫자나 넣어주세요 0을 넣으면 종료합니다"
n = input()
while n != 0
    sum = sum + n
    println "    >", sum
    n = input()
end
