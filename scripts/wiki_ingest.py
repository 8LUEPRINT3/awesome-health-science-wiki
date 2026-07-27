#!/usr/bin/env python3
"""Split the Foundations of Computer Vision textbook into wiki articles."""

import re
import os
import json
from pathlib import Path

RAW = Path("/home/asauce/.openclaw/workspace/raw/md/new_notebook.md")
WIKI = Path("/home/asauce/.openclaw/workspace/wiki")
WIKI.mkdir(exist_ok=True)

text = RAW.read_text(encoding="utf-8")
lines = text.split("\n")

# ── Chapter boundaries ──
# Find all top-level headings and classify them
chapters = []  # (line_idx, heading_text)
for i, line in enumerate(lines):
    if line.startswith("# ") and not line.startswith("## "):
        heading = line[2:].strip()
        chapters.append((i, heading))

# Identify which headings are actual chapters (numbered) vs front/back matter
# Chapters: "1  The Challenge of Vision" ... "55  A Simple Vision System—Revisited"
# Parts: "I   FOUNDATIONS", "II   IMAGE FORMATION", etc. (Roman numerals)
# Front matter: "Contents", "Preface", "Notation"
# Back matter: "Bibliography", "Index"

def classify(idx, heading):
    """Return (type, number, title) or None to skip."""
    # Skip Contents
    if heading == "Contents":
        return ("skip", None, None)
    # Preface
    if heading == "Preface":
        return ("frontmatter", 0, "Preface")
    # Notation
    if heading == "Notation":
        return ("frontmatter", 0, "Notation")
    # Bibliography
    if heading == "Bibliography":
        return ("backmatter", 0, "Bibliography")
    # Index
    if heading == "Index":
        return ("skip", None, None)
    # Part headings (Roman numerals)
    if re.match(r'^[IVX]+\s', heading):
        return ("part", None, heading)
    # Numbered chapters
    m = re.match(r'^(\d+)\s+(.+)', heading)
    if m:
        return ("chapter", int(m.group(1)), m.group(2).strip())
    return ("skip", None, None)

# Build chapter list with boundaries
entries = []
for idx, (line_idx, heading) in enumerate(chapters):
    result = classify(line_idx, heading)
    if result[0] == "skip":
        continue
    entries.append((line_idx, heading, result))

# Add end boundary
entries.append((len(lines), "END", ("end", None, None)))

# ── Tag mapping ──
TAG_MAP = {
    1: ["computer-vision", "perception", "history", "theory"],
    2: ["vision-systems", "blocks-world", "edge-detection", "inference"],
    3: ["image-analysis", "perception", "visual-cues"],
    4: ["ethics", "fairness", "bias", "privacy", "society"],
    5: ["image-formation", "light", "pinhole-camera", "projection"],
    6: ["optics", "lenses", "depth-of-field"],
    7: ["linear-systems", "cameras", "imaging"],
    8: ["color", "perception", "spectra", "colorimetry"],
    9: ["machine-learning", "learning-theory", "introduction"],
    10: ["gradient-descent", "optimization", "learning-algorithms"],
    11: ["generalization", "overfitting", "regularization"],
    12: ["neural-networks", "deep-learning", "architectures"],
    13: ["neural-networks", "distribution-transformers", "theory"],
    14: ["backpropagation", "gradient-computation", "training"],
    15: ["linear-filtering", "convolution", "image-processing"],
    16: ["fourier-analysis", "frequency-domain", "signal-processing"],
    17: ["blur-filters", "smoothing", "image-processing"],
    18: ["image-derivatives", "edges", "gradients"],
    19: ["temporal-filters", "video", "motion"],
    20: ["sampling", "aliasing", "nyquist"],
    21: ["downsampling", "upsampling", "interpolation"],
    22: ["filter-banks", "subband", "wavelets"],
    23: ["image-pyramids", "multiscale", "laplacian"],
    24: ["cnn", "convolutional-neural-networks", "deep-learning", "architectures"],
    25: ["rnn", "recurrent-neural-networks", "sequential"],
    26: ["transformers", "attention", "self-attention", "architectures"],
    27: ["statistical-models", "image-statistics", "probability"],
    28: ["textures", "synthesis", "analysis"],
    29: ["graphical-models", "probability", "inference"],
    30: ["representation-learning", "features", "embeddings"],
    31: ["perceptual-grouping", "gestalt", "segmentation"],
    32: ["generative-models", "synthesis", "vae", "gan"],
    33: ["generative-models", "representation-learning", "diffusion"],
    34: ["conditional-generation", "generative-models", "text-to-image"],
    35: ["data-bias", "domain-shift", "distribution-shift"],
    36: ["robustness", "adversarial", "augmentation"],
    37: ["transfer-learning", "fine-tuning", "domain-adaptation"],
    38: ["geometry", "3d", "representations"],
    39: ["camera-model", "calibration", "intrinsics", "extrinsics"],
    40: ["stereo-vision", "depth", "disparity", "matching"],
    41: ["homographies", "projective-geometry", "warping"],
    42: ["single-view", "metrology", "measurement"],
    43: ["depth-estimation", "monocular", "learning"],
    44: ["structure-from-motion", "multiview", "3d-reconstruction"],
    45: ["radiance-fields", "nerf", "novel-view-synthesis"],
    46: ["motion-estimation", "optical-flow", "tracking"],
    47: ["3d-motion", "ego-motion", "projection"],
    48: ["optical-flow", "estimation", "motion"],
    49: ["motion-learning", "video", "deep-learning"],
    50: ["object-recognition", "classification", "detection"],
    51: ["vision-language", "multimodal", "grounding"],
    52: ["research", "methodology"],
    53: ["writing", "papers", "communication"],
    54: ["presentations", "talks", "communication"],
    55: ["vision-systems", "revisited", "synthesis"],
}

# ── Wiki link injection ──
# Map of terms to wiki pages (longest match first)
LINK_MAP = {
    "convolutional neural network": "Convolutional Neural Networks",
    "convolutional neural net": "Convolutional Neural Networks",
    "CNN": "Convolutional Neural Networks",
    "backpropagation": "Backpropagation",
    "neural network": "Neural Networks",
    "deep learning": "Neural Networks",
    "image formation": "Image Formation",
    "color theory": "Color Theory",
    "linear filter": "Linear Filtering",
    "fourier analysis": "Fourier Analysis",
    "Fourier transform": "Fourier Analysis",
    "transformer": "Transformers",
    "generative model": "Generative Models",
    "computer vision": "Computer Vision",
    "machine learning": "Machine Learning",
    "optical flow": "Optical Flow",
    "stereo vision": "Stereo Vision",
    "structure from motion": "Structure from Motion",
    "transfer learning": "Transfer Learning",
    "representation learning": "Representation Learning",
    "gradient descent": "Gradient Descent",
    "diffusion model": "Diffusion Models",
    "NeRF": "Radiance Fields",
    "radiance field": "Radiance Fields",
    "object recognition": "Object Recognition",
    "image pyramid": "Image Pyramids",
    "filter bank": "Filter Banks",
    "pinhole camera": "Pinhole Camera",
    "depth estimation": "Depth Estimation",
    "domain adaptation": "Domain Adaptation",
    "adversarial": "Adversarial Robustness",
    "data augmentation": "Data Augmentation",
    "self-attention": "Attention Mechanism",
    "attention mechanism": "Attention Mechanism",
    "variational autoencoder": "Variational Autoencoders",
    "VAE": "Variational Autoencoders",
    "GAN": "Generative Adversarial Networks",
    "generative adversarial network": "Generative Adversarial Networks",
}

# Sort by length descending for longest-match-first
sorted_links = sorted(LINK_MAP.keys(), key=len, reverse=True)

def inject_links(text, current_chapter_num=None):
    """Add [[wiki links]] to text, avoiding double-linking and nesting."""
    # First pass: find all existing wiki link spans so we never touch them
    existing_spans = [(m.start(), m.end()) for m in re.finditer(r'\[\[.*?\]\]', text)]
    
    def _in_existing(pos):
        return any(s <= pos < e for s, e in existing_spans)
    
    # Process each term, longest first
    for term in sorted_links:
        target = LINK_MAP[term]
        pattern = re.compile(re.escape(term), re.IGNORECASE)
        m = pattern.search(text)
        while m:
            start, end = m.start(), m.end()
            # Skip if inside an existing wiki link
            if _in_existing(start):
                m = pattern.search(text, end)
                continue
            # Skip if inside a code block (rough check)
            before = text[:start]
            if before.count('```') % 2 == 1:
                m = pattern.search(text, end)
                continue
            # Replace
            replacement = f'[[{target}|{m.group()}]]'
            text = text[:start] + replacement + text[end:]
            # Update existing spans
            delta = len(replacement) - (end - start)
            existing_spans = [(s + delta if s >= end else s, e + delta if e >= end else e) for s, e in existing_spans]
            existing_spans.append((start, start + len(replacement)))
            m = pattern.search(text, start + len(replacement))
    return text

def clean_content(text):
    """Remove junk from content."""
    # Remove image references
    text = re.sub(r'!\[.*?\]\(.*?\)', '', text)
    # Remove HTML tags
    text = re.sub(r'<[^>]+>', '', text)
    # Remove standalone page numbers (lines that are just numbers)
    text = re.sub(r'^\d+\s*$', '', text, flags=re.MULTILINE)
    # Remove d_r0 artifacts
    text = re.sub(r'd\\_r\d+', '', text)
    # Remove excessive blank lines (3+ → 2)
    text = re.sub(r'\n{4,}', '\n\n\n', text)
    # Remove .xhtml link references but keep text
    text = re.sub(r'\[([^\]]+)\]\([^)]*\.xhtml[^)]*\)', r'\1', text)
    return text.strip()

def slugify(title):
    """Convert title to filename-safe string."""
    s = re.sub(r'[^\w\s-]', '', title)
    s = re.sub(r'[\s]+', '_', s)
    return s.strip('_')

def make_summary(lines_content, max_len=200):
    """Extract a summary from the first few meaningful lines."""
    for line in lines_content:
        line = line.strip()
        if not line or line.startswith('#') or line.startswith('!') or line.startswith('---'):
            continue
        if len(line) > 30:
            return line[:max_len].rstrip() + ('...' if len(line) > max_len else '')
    return "Chapter from Foundations of Computer Vision."

# ── Process chapters ──
created_files = []
i = 0
while i < len(entries) - 1:
    line_idx, heading, (etype, num, title) = entries[i]
    next_line_idx = entries[i + 1][0]

    if etype == "part":
        # Skip part headers, but record them
        i += 1
        continue

    if etype == "frontmatter":
        slug = slugify(title)
        filename = f"{slug}.md"
    elif etype == "backmatter":
        slug = slugify(title)
        filename = f"{slug}.md"
    elif etype == "chapter":
        slug = slugify(title)
        filename = f"Chapter_{num:02d}_{slug}.md"
    else:
        i += 1
        continue

    # Extract content
    content_lines = lines[line_idx:next_line_idx]
    content_text = '\n'.join(content_lines)

    # Clean
    content_text = clean_content(content_text)

    # Remove the heading itself (we'll add it back via frontmatter title)
    content_text = re.sub(r'^# .+\n', '', content_text, count=1)

    # Inject wiki links
    content_text = inject_links(content_text, num)

    # Get summary
    summary = make_summary(content_text.split('\n'))

    # Tags
    tags = TAG_MAP.get(num, ["computer-vision"]) if num else ["reference"]

    # Build frontmatter
    frontmatter = f"""---
title: "{title if title else heading}"
tags: [{', '.join(f'"{t}"' for t in tags)}]
created: 2026-07-24
summary: "{summary.replace('"', "'")}"
source: "raw/md/new_notebook.md"
---

"""

    # Write file
    filepath = WIKI / filename
    filepath.write_text(frontmatter + content_text, encoding='utf-8')
    created_files.append((filename, title or heading, num))
    print(f"  ✅ {filename}")
    i += 1

# ── Concept/topic stub files ──
concepts = {
    "Computer Vision": {
        "tags": ["computer-vision", "hub"],
        "summary": "The field of enabling machines to interpret and understand visual information from the world.",
        "content": """# Computer Vision

Computer vision is the interdisciplinary field of enabling machines to interpret and understand visual information. It spans [[Image Formation]], [[Machine Learning]], geometry, and perception.

## Core Areas

- [[Image Formation]] — How light becomes images
- [[Linear Filtering]] — Foundational image processing
- [[Fourier Analysis]] — Frequency-domain methods
- [[Neural Networks]] — Learning-based approaches
- [[Convolutional Neural Networks]] — The workhorse of modern vision
- [[Transformers]] — Attention-based architectures
- [[Generative Models]] — Creating and synthesizing images
- [[Stereo Vision]] — Depth from two views
- [[Optical Flow]] — Motion estimation
- [[Object Recognition]] — Classification and detection

## Textbook Chapters

This wiki contains all chapters from *Foundations of Computer Vision* (Torralba, Isola, Freeman, MIT Press 2024). See [[index]] for the full listing.
""",
    },
    "Convolutional Neural Networks": {
        "tags": ["cnn", "deep-learning", "architecture"],
        "summary": "Neural network architectures that use convolution operations, forming the backbone of modern computer vision.",
        "content": """# Convolutional Neural Networks

Convolutional Neural Networks (CNNs/ConvNets) are the dominant architecture in modern [[Computer Vision]]. They apply learned [[Linear Filtering|convolutional filters]] across spatial locations, building hierarchical feature representations.

## Key Concepts

- **Convolution layers** — Apply learned filters spatially
- **Pooling** — Spatial downsampling for efficiency and invariance
- **Receptive fields** — The region of input each neuron sees
- **Feature hierarchies** — From edges to textures to object parts

## Related Chapters

- [[Chapter_24_Convolutional_Neural_Nets]] — Full chapter on CNNs
- [[Chapter_12_Neural_Networks]] — Foundations of neural networks
- [[Chapter_14_Backpropagation]] — How CNNs are trained

## Related Concepts

- [[Neural Networks]]
- [[Transformers]]
- [[Image Pyramids]]
""",
    },
    "Backpropagation": {
        "tags": ["backpropagation", "training", "optimization"],
        "summary": "The algorithm for computing gradients in neural networks via the chain rule, enabling gradient-based learning.",
        "content": """# Backpropagation

Backpropagation is the core algorithm for training [[Neural Networks]]. It efficiently computes gradients of the loss function with respect to all parameters using the chain rule, enabling [[Gradient Descent|gradient-based optimization]].

## Key Ideas

- **Chain rule** — Decompose gradients through layers
- **Computational graph** — Forward and backward passes
- **Automatic differentiation** — The practical implementation

## Related Chapters

- [[Chapter_14_Backpropagation]] — Full chapter
- [[Chapter_10_Gradient-Based_Learning_Algorithms]] — Gradient descent methods
- [[Chapter_12_Neural_Networks]] — Network architectures
""",
    },
    "Neural Networks": {
        "tags": ["neural-networks", "deep-learning", "foundations"],
        "summary": "Computational models inspired by biological neurons, forming the basis of deep learning.",
        "content": """# Neural Networks

Neural networks are the foundational computational models behind modern [[Computer Vision]] and machine learning. They compose simple nonlinear units into deep architectures capable of learning complex mappings.

## Types

- **Feedforward networks** — Basic multilayer perceptrons
- [[Convolutional Neural Networks]] — Spatial/vision tasks
- **Recurrent networks** — Sequential data
- [[Transformers]] — Attention-based architectures

## Related Chapters

- [[Chapter_12_Neural_Networks]] — Introduction to neural networks
- [[Chapter_13_Neural_Networks_as_Distribution_Transformers]] — Theoretical perspective
- [[Chapter_14_Backpropagation]] — Training algorithm
""",
    },
    "Image Formation": {
        "tags": ["image-formation", "optics", "geometry"],
        "summary": "The physical and mathematical process by which light interacting with scenes creates images.",
        "content": """# Image Formation

Image formation describes how light from a scene is captured to create a 2D image. Understanding this process is fundamental to [[Computer Vision]].

## Key Topics

- **Light-surface interaction** — Lambertian and specular reflection
- [[Pinhole Camera]] — The simplest camera model
- **Perspective projection** — How 3D maps to 2D
- **Orthographic projection** — Parallel projection approximation
- **Lenses** — Real optical systems

## Related Chapters

- [[Chapter_05_Imaging]] — Light and surfaces
- [[Chapter_06_Lenses]] — Optical systems
- [[Chapter_07_Cameras_as_Linear_Systems]] — Linear systems perspective
- [[Chapter_08_Color]] — Color formation and perception
""",
    },
    "Color Theory": {
        "tags": ["color", "perception", "physics"],
        "summary": "The physics and perception of color, including spectra, matching, and representation.",
        "content": """# Color Theory

Color theory encompasses the physics of light, the biology of color perception, and the mathematical representation of color in [[Computer Vision]].

## Key Topics

- **Spectral power distribution** — Light as a function of wavelength
- **Color matching** — How humans perceive color
- **Metamerism** — Different spectra that appear identical
- **Color spaces** — RGB, XYZ, LAB representations

## Related Chapters

- [[Chapter_08_Color]] — Full chapter on color
""",
    },
    "Linear Filtering": {
        "tags": ["filtering", "convolution", "image-processing"],
        "summary": "Foundational image processing operations based on convolution and linear systems.",
        "content": """# Linear Filtering

Linear filtering is the foundation of classical image processing in [[Computer Vision]]. It involves convolving images with kernels to achieve smoothing, sharpening, edge detection, and more.

## Key Topics

- **Convolution** — The core operation
- **Impulse response** — Characterizing filters
- **Frequency response** — Connection to [[Fourier Analysis]]
- **Separability** — Efficient computation

## Related Chapters

- [[Chapter_15_Linear_Image_Filtering]] — Full chapter
- [[Chapter_17_Blur_Filters]] — Smoothing filters
- [[Chapter_18_Image_Derivatives]] — Gradient filters
""",
    },
    "Fourier Analysis": {
        "tags": ["fourier", "frequency", "signal-processing"],
        "summary": "Mathematical framework for analyzing signals and images in the frequency domain.",
        "content": """# Fourier Analysis

Fourier analysis decomposes signals and images into sinusoidal components, providing a frequency-domain perspective essential to [[Computer Vision]] and [[Linear Filtering]].

## Key Topics

- **Fourier transform** — Spatial ↔ frequency domain
- **Convolution theorem** — Convolution = multiplication in frequency
- **Sampling theory** — Nyquist rate and aliasing
- **Filter design** — Frequency-domain filter specification

## Related Chapters

- [[Chapter_16_Fourier_Analysis]] — Full chapter
- [[Chapter_20_Image_Sampling_and_Aliasing]] — Sampling theory
""",
    },
    "Transformers": {
        "tags": ["transformers", "attention", "architecture"],
        "summary": "Attention-based neural network architectures that have become dominant in vision and language.",
        "content": """# Transformers

Transformers are neural network architectures based on self-attention mechanisms. Originally developed for NLP, they have become central to modern [[Computer Vision]] through Vision Transformers (ViTs).

## Key Concepts

- **Self-attention** — Relating all positions in a sequence
- **Multi-head attention** — Multiple attention perspectives
- **Positional encoding** — Injecting spatial/sequential information
- **Vision Transformer (ViT)** — Transformers for images

## Related Chapters

- [[Chapter_26_Transformers]] — Full chapter
- [[Chapter_12_Neural_Networks]] — Neural network foundations

## Related Concepts

- [[Neural Networks]]
- [[Convolutional Neural Networks]]
""",
    },
    "Generative Models": {
        "tags": ["generative-models", "synthesis", "deep-learning"],
        "summary": "Models that learn to generate new images and visual content, including VAEs, GANs, and diffusion models.",
        "content": """# Generative Models

Generative models learn to create new images and visual content. They are central to modern [[Computer Vision]], powering text-to-image generation, image editing, and representation learning.

## Types

- **Variational Autoencoders (VAEs)** — Latent variable models
- **Generative Adversarial Networks (GANs)** — Adversarial training
- **Diffusion models** — Iterative denoising
- **Autoregressive models** — Sequential generation

## Related Chapters

- [[Chapter_32_Generative_Models]] — Foundations
- [[Chapter_33_Generative_Modeling_Meets_Representation_Learning]] — Advanced topics
- [[Chapter_34_Conditional_Generative_Models]] — Conditional generation

## Related Concepts

- [[Representation Learning]]
- [[Neural Networks]]
""",
    },
}

for name, info in concepts.items():
    filename = f"{name.replace(' ', '_')}.md"
    filepath = WIKI / filename
    frontmatter = f"""---
title: "{name}"
tags: [{', '.join(f'"{t}"' for t in info['tags'])}]
created: 2026-07-24
summary: "{info['summary']}"
source: "raw/md/new_notebook.md"
---

"""
    filepath.write_text(frontmatter + info['content'], encoding='utf-8')
    created_files.append((filename, name, None))
    print(f"  📄 {filename}")

# ── Index ──
chapter_files = [(f, t, n) for f, t, n in created_files if n is not None and n > 0]
chapter_files.sort(key=lambda x: x[2])

index_content = """---
title: "Foundations of Computer Vision — Wiki Index"
tags: ["index", "computer-vision", "textbook"]
created: 2026-07-24
summary: "Complete index of all wiki articles generated from Foundations of Computer Vision (Torralba, Isola, Freeman, MIT Press 2024)."
source: "raw/md/new_notebook.md"
---

# Foundations of Computer Vision — Wiki Index

*Based on the textbook by Antonio Torralba, Phillip Isola, and William T. Freeman (MIT Press, 2024).*

## Concept Hub

- [[Computer Vision]] — Main hub
- [[Neural Networks]] — Foundations of deep learning
- [[Convolutional Neural Networks]] — CNNs
- [[Transformers]] — Attention architectures
- [[Generative Models]] — Image synthesis
- [[Image Formation]] — Optics and cameras
- [[Color Theory]] — Color science
- [[Linear Filtering]] — Image processing
- [[Fourier Analysis]] — Frequency methods
- [[Backpropagation]] — Training algorithm

## All Chapters

### Part I: Foundations
"""
for f, t, n in chapter_files:
    if n <= 4:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part II: Image Formation\n"
for f, t, n in chapter_files:
    if 5 <= n <= 8:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part III: Foundations of Learning\n"
for f, t, n in chapter_files:
    if 9 <= n <= 14:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part IV: Foundations of Image Processing\n"
for f, t, n in chapter_files:
    if 15 <= n <= 16:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part V: Linear Filters\n"
for f, t, n in chapter_files:
    if 17 <= n <= 19:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part VI: Sampling and Multiscale\n"
for f, t, n in chapter_files:
    if 20 <= n <= 23:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part VII: Neural Architectures\n"
for f, t, n in chapter_files:
    if 24 <= n <= 26:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part VIII: Probabilistic Models\n"
for f, t, n in chapter_files:
    if 27 <= n <= 29:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part IX: Generative Models & Representation Learning\n"
for f, t, n in chapter_files:
    if 30 <= n <= 34:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part X: Challenges in Learning-Based Vision\n"
for f, t, n in chapter_files:
    if 35 <= n <= 37:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part XI: Understanding Geometry\n"
for f, t, n in chapter_files:
    if 38 <= n <= 45:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part XII: Understanding Motion\n"
for f, t, n in chapter_files:
    if 46 <= n <= 49:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part XIII: Vision with Language\n"
for f, t, n in chapter_files:
    if 50 <= n <= 51:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part XIV: Research, Writing & Speaking\n"
for f, t, n in chapter_files:
    if 52 <= n <= 54:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n### Part XV: Closing\n"
for f, t, n in chapter_files:
    if n >= 55:
        link = f.replace('.md', '')
        index_content += f"- [[{link}|Chapter {n}: {t}]]\n"

index_content += "\n## Front Matter\n\n- [[Preface]]\n- [[Notation]]\n"
index_content += "\n## Back Matter\n\n- [[Bibliography]]\n"

(WIKI / "index.md").write_text(index_content, encoding='utf-8')
print(f"\n  📋 index.md")

print(f"\n✅ Done! Created {len(created_files) + 1} files in wiki/")
