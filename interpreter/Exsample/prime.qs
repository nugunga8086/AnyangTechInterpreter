func is_prime(n)
    return 0 ? n == 1       // 어쩌다 보니 알게 된 사실, <- 이 문법은 yield return 과 같은 의미임

    for i=2 to n - 1
        if n % i == 0
            return 0
        end
    end
    return 1
end

func main()

    for n=1 to 1000
        if is_prime(n)
            print n, " "
        end
    end
    println ""
end

