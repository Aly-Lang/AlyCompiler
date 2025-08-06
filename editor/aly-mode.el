;;; aly-mode.el --- A major mode for editing the Aly language... -*- lexical-binding: t -*-

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

;; Gather all keyword font locks together into big daddy keyword font-lock
(setq un--font-lock-defaults
      (let* ((keywords '("if" "else"))
             (binary-operators '("+" "*" "-" "/"
                                 "<" ">"
                                 ":" "=" ":="
                                 "&" "@"))

             (,keywords-regex (regexp-opt keywords 'words))
             (,binary-operators-regex (regexp-opt binary-operators 'words))
             (,builtin-types-regex (rx (zero-or-more "@")
                                      (or "integer")))
             )
        `((,keywords-regex . 'font-lock-keyword-face)
          (,builtin-types-regex . 'font-lock-type-face)
          (,binary-operators-regex . nil)
          )))

(define-derived-mode aly-mode prog-mode
  "unnamed"
  (setq font-lock-defaults '(un--font-lock-defaults)))

;;; aly-mode.el ends here