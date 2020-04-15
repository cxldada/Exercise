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

(mapcar #'(lambda (x) (+ x 10))
        '(1 2 3)
        )

(mapcar #'list
        '(a b c)
        '(1 2 3 4)
        )

(maplist
 #'(lambda (x) x)
 '(a b c)
 )

(defun cxldada-copy-tree (tr)
  (if (atom tr)
      tr
      (cons (cxldada-copy-tree (car tr))
            (cxldada-copy-tree (cdr tr))
            )
      )
  )

(cxldada-copy-tree '(a (b c) d))

(member 'b '(a b c))

(member '(a) '((b) (a)) :test #'equal)

(member 'a '((a b) (c d)) :key #'car)

(member-if #'oddp '(2 3 4))

(defun cxldada-member-if (fn lst)
  (and (consp lst)
       (if (funcall fn (car lst))
           lst
           (cxldada-member-if fn (cdr lst))
           )
       )
  )

(cxldada-member-if #'oddp '(2 3 4))

(adjoin 'b '(a b c))

(adjoin 'z '(a b c))

(union '(a b c) '(c b s))

(intersection '(a b c) '(b b c))

(set-difference '(a b c d e) '(b e))

(set-difference '(b e) '(a b c d e))

;; sequences
(length '(a b c))

(subseq '(a b c d e) 0 4)
(subseq '(a b c d e) 1)

(reverse '(a b c))

(defun mirror? (s)
  (let
      ((len (length s)))
    (and (evenp len)
         (let ((mid (/ len 2)))
           (equal (subseq s 0 mid)
                  (reverse (subseq s mid))
                  )
           ))
      )
  )

(mirror? '(a c b a))


















































