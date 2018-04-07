(TeX-add-style-hook
 "study"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "a4")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "booktabs"
    "siunitx")
   (LaTeX-add-labels
    "tab:runtimes"))
 :latex)

