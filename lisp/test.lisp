(+ 2 3 4 5)
(/ (- 7 1) (+ 2 10))

;; quote expression
(quote (a + 1))

;; use ' represent "quote"
'(a + 1)

;; symbol: anything english words
'abced

;; list
'(1 2 3)

;; differences betwee lists and expression
(list '(+ 2 1) (+ 2 1))

;; use "cons" to create new lists
(cons 'a '(bc d 1))

;; use "car" get the first element of the lists
(car '(a b c))

;; use "cdr" get other element except the first element int the list
(cdr '(a b c))

;; use "t" represent "true"
(listp '(a b))

;; use "nil" represent "false"
(listp (cons 2 nil))

;; if-then-else expression
(if (listp '(a b c))
    (+ 1 2)
    (+ 1 3))

;; and macro
(and 1 nil 2)

;; or macro
(or nil "haha" 1 nil)

;; define functions
(defun out-third (x)
  (car (cdr (cdr x)))
  )

;; recursion functions
(defun cxldada-member (obj lst)
  (if (null lst)
      nil
      (if (eql obj (car lst))
          lst
          (cxldada-member obj (cdr lst))))
  )

;; (cxldada-member 'b '(a b c))

;; output functions
(format t "~A plus ~A equals ~A. ~%" 2 3 (+ 2 3))

;; input functions
(defun cxldada-askem (string)
  (format t "~A" string)
  (read)
  )

;; (cxldada-askem "How old are you?")

;; local variable
(defun cxldada-test()
  (let ((x (read)) (y (read)))
    (+ x y)
    )
  )

;; (cxldada-test)

;; global variable
(defparameter cxldada-haha 1)

;; global constant variable
(defconstant limit (+ cxldada-haha 1))

;; Determine wheher it is a constant or global variable
(boundp 'limit)

;; assignment operator
(setf cxldada-haha 100)
;; cxldada-haha

;; "do" is macro
(defun cxldada-show-squares (start end)
  (do ((i start (+ i 1)))
      ((> i end) 'done)
    (format t "~A ~A~%" i (* i i))
      )
  )

;; (cxldada-show-squares 1 10)


;; progn
(defun cxldada-show-squares-progn (i end)
  (if (> i end)
      'done
      (progn
        (format t "~A ~A~%" i (* i i))
        (cxldada-show-squares-progn (+ i 1) end)
        )
      )
  )

;; (cxldada-show-squares-progn 1 10)

;; dolist
(defun cxldada-length (lst)
  (let ((len 0))
    (dolist (obj lst)
      (setf len (+ len 1)))
    len
    )
  )
;;(cxldada-length '(a b c d))

;; function
(function +)

;; use #' represent function
#'+

;; apply
(apply #'+ '(1 2 3 4))

;; funcall
(funcall #'+ 1 2 3 4)

;; lambda
((lambda (x) (+ x 100)) 22)

(funcall #'(lambda (x) (+ x 121))
         22)

;;;;;;;;;;;;;; exercises
(+ (- 5 1) (+ 3 7))

(list 1 (+ 2 3))

(if (listp 1) (+ 1 2) (+ 3 4))

(list (and (listp 3) t) (+ 1 2))





























































































