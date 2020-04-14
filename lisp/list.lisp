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

;; Example: compression
;; run-length encoding
(defun cxldada-compress (x)
  (if (consp x)
      (cxldada-compr (car x) 1 (cdr x))
      x
      )
  )

(defun cxldada-compr (elt n lst)
  (if (null lst)
      (list (n-elts elt n))
      (let ((next (car lst)))
        (if (eql next elt)
            (cxldada-compr elt (+ n 1) (cdr lst))
            (cons (n-elts elt n)
                  (cxldada-compr next 1 (cdr lst)))
            )
        )
      )
  )

(defun n-elts (elt n)
  (if (> n 1)
      (list n elt)
      elt
      )
  )

(cxldada-compress '(1 1 1 0 1 0 0 0 0 1))

(defun cxldada-uncompress (lst)
  (if (null lst)
      nil
      (let ((elt (car lst))
            (rest (uncompress (cdr lst))))
        (if (consp elt)
            (append (apply #'list-of elt)
                    rest)
            (cons elt rest)))))

(defun list-of (n elt)
  (if (zerop n)
      nil
      (cons elt (list-of (- n 1) elt))))

;; Access
(nth 0 '(a b c))

(nthcdr 2 '(a b c))

(defun cxldada-nthcdr (n lst)
  (if (equal n 0)
      lst
      (cxldada-nthcdr (- n 1) (cdr lst))
      )
  )

(cxldada-nthcdr 2 '(a b c))

(last '(a b c))













































































