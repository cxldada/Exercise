;; when you call "cons" lisp well create two pointer;
;; "car" is first pointer
;; "cdr" is second pointer
(setf x (cons 'a '(b c d)))
(car x)
(cdr x)

;; equality

;; the following expression is not equal
;; because it is two different objects;
(eql (cons 'a nil) (cons 'a nil))

(setf y (cons 'a '(b c d)))

(equal x '(a b c d))

(defun cxldada-equal (x y)
  (or (eql x y)
      (and (consp x)
           (consp y)
           (cxldada-equal (car x) (car y))
           (cxldada-equal (cdr x) (cdr y))
           )
      )
  )

;;(cxldada-equal x y)

(setf x '(a b c)
      y (copy-list x)
      )

(defun cxldada-copy-list (lst)
  (if (atom lst)
      lst
      (cons (car lst) (our-copy-list (cdr lst)))
      )
  )

;;(append '(a b) '(c d) '(e) '(f g))


























































































