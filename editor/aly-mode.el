;;; aly-mode.el --- A major mode for editing the aly language that the aly compiler compiles... -*- lexical-binding: t -*-

;;; Code:

(defvar aly-mode-syntax-table
  (make-syntax-table)
  "Syntax table for aly-mode")

;; Set semi-colon as comment starting character.
(modify-syntax-entry
 ?\; "<"
 aly-mode-syntax-table)
;; Set hash/pound as comment starting character.
(modify-syntax-entry
 ?# "<"
 aly-mode-syntax-table)
;; Set newline as comment ending character.
(modify-syntax-entry
 ?\n ">"
 aly-mode-syntax-table)

;; Delimiters include comma
(modify-syntax-entry
 ?, "."
 aly-mode-syntax-table)

;; Allowed within symbols: _-#$
(modify-syntax-entry
 ?_ "_"
 aly-mode-syntax-table)
(modify-syntax-entry
 ?- "_"
 aly-mode-syntax-table)
(modify-syntax-entry
 ?# "_"
 aly-mode-syntax-table)
(modify-syntax-entry
 ?$ "_"
 aly-mode-syntax-table)

;; Parenthesis
(modify-syntax-entry
 ?\( "()"
 aly-mode-syntax-table)
(modify-syntax-entry
 ?\) ")("
 aly-mode-syntax-table)
(modify-syntax-entry
 ?\[ "(]"
 aly-mode-syntax-table)
(modify-syntax-entry
 ?\] ")["
 aly-mode-syntax-table)
(modify-syntax-entry
 ?{ "(}"
 aly-mode-syntax-table)
(modify-syntax-entry
 ?} "){"
 aly-mode-syntax-table)

;; Unary prefix operators
;; Addressof
(modify-syntax-entry
 ?& "'"
 aly-mode-syntax-table)
;; Dereference
(modify-syntax-entry
 ?@ "'"
 aly-mode-syntax-table)

(defconst un--font-lock-operators
  (list
   ;; Matching Regexp
   (rx (or
        "+" "*" "-" "/"
        "<" ">"
        ":" "=" ":="
        "&" "@"
        ))
   '(0 nil)
   ))

(defconst un--font-lock-generic
  (list
   ;; Matching Regexp
   (rx (or "defun" "if" "else"))
   ;; Font face to use
   '(0 font-lock-keyword-face)
   ))

(defconst un--font-lock-function-name
  (list
   ;; Matching Regexp
   (rx "defun" whitespace
       (group (* (or (not whitespace) "("))))
   ;; Font face to use
   '1
   'font-lock-function-name-face
   ))

(defconst un--font-lock-builtin-types
  (list
   ;; Matching Regexp
   (rx (zero-or-more "@")
       (or "integer" "function"))
   ;; Font face to use
   '(0 font-lock-type-face)
   ))

;; Gather all keyword font locks together into keyword font-lock
(defconst un--font-lock
  (list
   un--font-lock-builtin-types
   un--font-lock-operators
   un--font-lock-function-name
   un--font-lock-generic
   ))

(define-derived-mode aly-mode prog-mode
  "aly"
  (setq font-lock-defaults '(un--font-lock)))

;;; aly-mode.el ends here