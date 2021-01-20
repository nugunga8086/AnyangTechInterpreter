
func is_prime(n)
    return $false ? n == 1 or n < 0 // <- 이 문법은 뒤에 있는 조건식이 참일 때만 0을 반환 아니라면 밑에 실행

    for i=2 to n - 1
        if n % i == 0
            return $false
        end
    end
    return $true
end

func main()

    $true = 1
    $false= 0

    for n=1 to 1000
        if is_prime(n)
            print n, " "
        end
    end
    println ""
end

