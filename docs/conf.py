from typing import List, Tuple
import pathlib
import re


CURRENT_FILE = pathlib.Path(__file__).resolve()
CURRENT_DIR = CURRENT_FILE.parent
PROJECT_DIR = CURRENT_DIR.parent


def read_authors(file: pathlib.Path) -> List[str]:
    with open(file) as f:
        return [l.strip() for l in f.readlines()]


def read_version(file: pathlib.Path) -> Tuple[int, int, int]:
    with open(file) as f:
        text = f.read()
        major = re.search("VERSION_MAJOR (\d+)", text).group(1)
        minor = re.search("VERSION_MINOR (\d+)", text).group(1)
        patch = re.search("VERSION_PATCH (\d+)", text).group(1)
        return major, minor, patch


project = "Ecole"
author = ", ".join(read_authors(PROJECT_DIR / "AUTHORS"))
copyright = author
version_major, version_minor, version_patch = read_version(PROJECT_DIR / "VERSION")
version = f"{version_major}.{version_minor}"
release = f"{version_major}.{version_minor}.{version_patch}"

extensions = [
    "sphinx.ext.autodoc",  # Read doc from Python docstrings
    "sphinx.ext.viewcode",
]

# Math setting
extensions += ["sphinx.ext.mathjax"]

# Code style
pygments_style = "monokai"

# Theme
extensions += ["sphinx_rtd_theme"]
html_theme = "sphinx_rtd_theme"
html_context = {
    "display_github": True,
    "github_user": "ds4dm",
    "github_repo": "ecole",
    "github_version": "master",  # For the edit on Github link
    "conf_py_path": "/docs/",  # For the edit on Github link
}
html_theme_options = {
    "logo_only": True,
}
html_logo = "_static/images/ecole-logo-bare.png"
html_favicon = "_static/favicon.ico"
# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]
html_style = "css/custom.css"

# Custom footer
templates_path = ["_templates"]

# Autodoc to read Python docstrings
extensions += ["sphinx.ext.autodoc"]
autodoc_default_options = {
    "members": True,  # Document all members
    "undoc-members": True,
}

# Breathe for Doxygen import
extensions += ["breathe"]
breathe_default_project = "libecole"


# Napoleon write docstrings in Numpy style
extensions += ["sphinx.ext.napoleon"]
napoleon_google_docstring = False
napoleon_numpy_docstring = True


# Preprocess docstring to remove "core" from type name
def preprocess_signature(app, what, name, obj, options, signature, return_annotation):
    if signature is not None:
        signature = signature.replace(".core", "")
    if return_annotation is not None:
        return_annotation = return_annotation.replace(".core", "")
    return signature, return_annotation


def setup(app):
    app.connect("autodoc-process-signature", preprocess_signature)
