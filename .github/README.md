# GitHub Pull Request Color Codes

Use `pull-request-colors.json` as the supported color list for pull request notes, status text, and review summaries.

GitHub Markdown does not support arbitrary colored text in pull request descriptions. It does render color swatches for supported color literals, so use the label text plus the color code when color context matters.

| Key       | Label   | Hex       | RGB                  | HSL                   | Text class         | Use                                         |
| --------- | ------- | --------- | -------------------- | --------------------- | ------------------ | ------------------------------------------- |
| `primary` | Primary | `#00d1b2` | `rgb(0, 209, 178)`   | `hsl(171, 100%, 41%)` | `has-text-primary` | Default highlighted status                  |
| `link`    | Link    | `#3273dc` | `rgb(50, 115, 220)`  | `hsl(217, 71%, 53%)`  | `has-text-link`    | External reference or documentation status  |
| `info`    | Info    | `#209cee` | `rgb(32, 156, 238)`  | `hsl(204, 86%, 53%)`  | `has-text-info`    | Informational status                        |
| `success` | Success | `#23d160` | `rgb(35, 209, 96)`   | `hsl(141, 71%, 48%)`  | `has-text-success` | Passed, completed, or ready                 |
| `warning` | Warning | `#ffdd57` | `rgb(255, 221, 87)`  | `hsl(48, 100%, 67%)`  | `has-text-warning` | Needs attention before merge                |
| `danger`  | Danger  | `#ff3860` | `rgb(255, 56, 96)`   | `hsl(348, 100%, 61%)` | `has-text-danger`  | Failed, blocked, or high risk               |
| `violet`  | Violet  | `#b86bff` | `rgb(184, 107, 255)` | `hsl(271, 100%, 71%)` | `has-text-violet`  | Terminal highlight or special note          |
| `light`   | Light   | `#f5f5f5` | `rgb(245, 245, 245)` | `hsl(0, 0%, 96%)`     | `has-text-light`   | Light mode foreground or contrast reference |
| `dark`    | Dark    | `#363636` | `rgb(54, 54, 54)`    | `hsl(0, 0%, 21%)`     | `has-text-dark`    | Dark mode foreground or contrast reference  |

Supported GitHub color literal formats:

```text
#RRGGBB
#RGB
rgb(r, g, b)
rgba(r, g, b, a)
hsl(h, s%, l%)
hsla(h, s%, l%, a)
```

Example pull request text:

```markdown
Status: Success `#23d160`
Risk: Warning `#ffdd57`
Blocked: Danger `#ff3860`
```
